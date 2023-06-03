#include "NetworkManager.h"
#include "Packet.h"

#include "../EntityComponent/Components/GameManager.h"
#include "../Scenes/ColorSelection.h"
#include "../EntityComponent/Components/Snake.h"
#include "../EntityComponent/Components/AppleGenerator.h"
#include "../EntityComponent/Entity.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/Scene.h"
#include "../Scenes/Battle.h"
#include "../Utils/SDLUtils.h"

#include "../EntityComponent/Entity.h"
#include "../EntityComponent/Components/Text.h"

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

NetworkManager::NetworkManager()
{
	mExitThread = false;
	mGameStarted = false;

	mClientId = 0;

	mAcceptFrequency = 150;
	mRecvFrequency = 50;
	mSendFrequency = 100;
	mClientFrequency = 50;

	mInitialized = false;

	mPlayerSockets = vector<Socket*>(MAX_PLAYERS);

	for(int i = 0; i < mPlayerSockets.size(); i++)
		mPlayerSockets[i] = nullptr;
}

NetworkManager::~NetworkManager()
{
	close();
}

bool NetworkManager::init(bool host, const char* ipAddress)
{
	mHost = host;

	if (mHost) { 	// Si somos un host
		assert(getNextPlayerId() == 0);
		mPlayerSockets[0] = new Socket(LOOPBACK, MULTISNAKE_PORT);
		mPlayerSockets[0]->bind();
		gameManager()->myId = 0;

		// Hilos
		accept_t = new std::thread(&NetworkManager::acceptPlayers, this);
		accept_t->detach();

		receiveplayers_t = new std::thread(&NetworkManager::receivePlayers, this);
		receiveplayers_t->detach();

		cout << "NetworkManager: host inicializado (" << gameManager()->myName << ")\n";
	}
	else { 			// Si somos un cliente
		//Pedimos conexion al host
		Socket* socket = new Socket(LOOPBACK, MULTISNAKE_PORT);
		socket->bind();

		Socket* hostSocket = new Socket(ipAddress, MULTISNAKE_PORT);

		Packet sendPacket;
		sendPacket.type = PACKETTYPE_CONNECTIONREQUEST;
		strcpy(sendPacket.info.connectionRequest.playerName, gameManager()->myName.c_str());

		int bytes = socket->send(sendPacket, *hostSocket);

		//Esperamos respuesta
		Socket* senderSocket = nullptr;

		Packet receivedPacket;
		receivedPacket.type = PACKETTYPE_NULL;

		cout << "NetworkManager: cliente " << gameManager()->myName << " a la espera de confirmacion (" << ipAddress << ")\n";

		while (receivedPacket.type != PACKETTYPE_CONNECTIONACCEPT && receivedPacket.type != PACKETTYPE_CONNECTIONDENY)
			socket->recv(receivedPacket, senderSocket);

		if (receivedPacket.type == PACKETTYPE_CONNECTIONDENY) { // Si nos rechazan porque la partida est� llena
			delete socket;
			delete hostSocket;
			return false;
		}

		std::cout << "Conexion aceptada" << endl;

		// Cuando nos acepte recibimos la informacion
		mClientId = receivedPacket.info.accept.playerId;
		gameManager()->myId = mClientId;

		mPlayerSockets[0] = hostSocket;
		mPlayerSockets[mClientId] = socket;

		strcpy(gameManager()->playerNames[0], receivedPacket.info.accept.playerName1);
		strcpy(gameManager()->playerNames[1], receivedPacket.info.accept.playerName2);
		strcpy(gameManager()->playerNames[2], receivedPacket.info.accept.playerName3);
		strcpy(gameManager()->playerNames[3], receivedPacket.info.accept.playerName4);
				
		// gameManager()->playerColors[0] = (SnakeColor) receivedPacket.info.accept.color1;
		// gameManager()->playerColors[1] = (SnakeColor) receivedPacket.info.accept.color2;
		// gameManager()->playerColors[2] = (SnakeColor) receivedPacket.info.accept.color3;
		// gameManager()->playerColors[3] = (SnakeColor) receivedPacket.info.accept.color4;

		gameManager()->myName = gameManager()->playerNames[mClientId];

		// Change scene (Prevent injection)
		std::vector<string> names(4, " ");
		names[0] = gameManager()->playerNames[0];
		names[1] = gameManager()->playerNames[1];
		names[2] = gameManager()->playerNames[2];
		names[3] = gameManager()->playerNames[3];

		std::vector<int> colors(4, -1);
		colors[0] = gameManager()->playerColors[0];
		colors[1] = gameManager()->playerColors[1];
		colors[2] = gameManager()->playerColors[2];
		colors[3] = gameManager()->playerColors[3];

		sceneManager().change(new ColorSelection(names, colors, false));

		updateclient_t = new std::thread(&NetworkManager::updateClient, this);
		updateclient_t->detach();
	}

	mInitialized = true;
	return true;
}

// SERVIDOR

// Funci�n que se encarga de aceptar a los jugadores (se encuentra en un hilo)

void NetworkManager::acceptPlayers()
{
	while (!mExitThread) {
		Packet receivedPacket;
		Socket* clientSocket = nullptr;

		int success = mPlayerSockets[0]->recv(receivedPacket, clientSocket);
        if (success < 0) continue;

		if(receivedPacket.type != PACKETTYPE_CONNECTIONREQUEST)
			continue;

		Packet replyPacket;

		// Rechazamos si el juego ha empezado o la sala esta llena
		int playerId = getNextPlayerId();
		if (mGameStarted || playerId == -1)
			replyPacket.type = PACKETTYPE_CONNECTIONDENY;
		else {
			mPlayerSockets[playerId] = clientSocket;

			strcpy(gameManager()->playerNames[playerId], receivedPacket.info.connectionRequest.playerName);

			std::cout << "Cliente conectado  Nombre: " << gameManager()->playerNames[playerId] << "  ID: " << playerId << "\n";

			replyPacket.type = PACKETTYPE_CONNECTIONACCEPT;
			replyPacket.info.accept.playerId = playerId;

			strcpy(replyPacket.info.accept.playerName1, gameManager()->playerNames[0]);
			strcpy(replyPacket.info.accept.playerName2, gameManager()->playerNames[1]);
			strcpy(replyPacket.info.accept.playerName3, gameManager()->playerNames[2]);
			strcpy(replyPacket.info.accept.playerName4, gameManager()->playerNames[3]);

			replyPacket.info.accept.color1 = gameManager()->playerColors[0];
			replyPacket.info.accept.color2 = gameManager()->playerColors[1];
			replyPacket.info.accept.color3 = gameManager()->playerColors[2];
			replyPacket.info.accept.color4 = gameManager()->playerColors[3];

			// Update textures
			string entName = "Player" + to_string(playerId + 1) + "Text";
			string newName = gameManager()->playerNames[playerId];

			SDL_Color color = {255,255,255,255};
			sceneManager().getActiveScene()->findEntity(entName).get()
			->getComponent<Text>("text")->setText(newName, color);

			//Informar al resto de jugadores
			Packet multicastPacket;
			multicastPacket.type = PACKETTYPE_CREATEPLAYER;

			multicastPacket.info.createPlayer.newPlayerId = playerId;
			strcpy(multicastPacket.info.createPlayer.newPlayerName, newName.c_str());

			for(int i = 1; i < mPlayerSockets.size(); i++)
				if (mPlayerSockets[i] != nullptr)
					mPlayerSockets[0]->send(multicastPacket, *mPlayerSockets[i]);
		}
		
		mPlayerSockets[0]->send(replyPacket, *clientSocket);

		SDL_Delay(mAcceptFrequency);
	}	
}

// Funci�n que se encarga de actualizar los jugadores (se encuentra en un hilo)
// Recibe los paquetes de todos los jugadores

void NetworkManager::receivePlayers()
{
	Packet receivedPacket;
	Socket* clientSocket;

	while (!mExitThread) {
		// Receive info from clients
		int success = mPlayerSockets[0]->recv(receivedPacket, clientSocket);
        if (success < 0) continue;

		switch (receivedPacket.type)
		{
		case PACKETTYPE_DISCONNECTIONREQUEST:
		{
			int disconnectionId = receivedPacket.info.disconnectionRequest.playerId;

			delete mPlayerSockets[disconnectionId];
			mPlayerSockets[disconnectionId] = nullptr;

			strcpy(gameManager()->playerNames[disconnectionId], " ");

			// Update texture
			string entName = "Player" + to_string(disconnectionId + 1) + "Text";
			SDL_Color color = {255,255,255,255};
			sceneManager().getActiveScene()->findEntity(entName).get()
				->getComponent<Text>("text")->setText(" ", color);

			Packet sendPacket;
			//Actualizo a los demas jugadores
			sendPacket.type = PACKETTYPE_DISCONNECTIONREQUEST;
			sendPacket.info.disconnectionRequest.playerId = disconnectionId;

			for(int i = 1; i < mPlayerSockets.size(); i++)
				if (mPlayerSockets[i] != nullptr)
					mPlayerSockets[0]->send(sendPacket, *mPlayerSockets[i]);
		}
			break;
		case PACKETTYPE_SYNCSNAKE:
			//Actualizo la serpiente
			sceneManager().getActiveScene()->findEntity("Snake" + to_string(receivedPacket.info.snake.id)).get()
				->getComponent<Snake>("snake")
				->turn(Vector2(receivedPacket.info.snake.orientationX, receivedPacket.info.snake.orientationY));

			//Reenvio a los demas jugadores
			for(int i = 1; i < mPlayerSockets.size(); i++)
				if (mPlayerSockets[i] != nullptr && i != receivedPacket.info.snake.id)
					mPlayerSockets[0]->send(receivedPacket, *mPlayerSockets[i]);
			break;
		case PACKETTYPE_SYNCAPPLE:
			//Actualizo la manzana
			if(receivedPacket.info.apple.snakeId != 0) 
				//Los clientes solo pueden comer manzanas
				for(Apple& apple : sceneManager().getActiveScene()->findEntity("AppleGenerator").get()
					->getComponent<AppleGenerator>("applegenerator")->getApples())
					if(apple.posX == receivedPacket.info.apple.positionX && apple.posY == receivedPacket.info.apple.positionY)
						sceneManager().getActiveScene()->findEntity("Snake" + to_string(receivedPacket.info.apple.snakeId)).get()
							->getComponent<Snake>("snake")->eatApple(apple);
					
			//Reenvio a los demas jugadores
			for(int i = 1; i < mPlayerSockets.size(); i++)
				if (mPlayerSockets[i] != nullptr && i != receivedPacket.info.apple.snakeId)
					mPlayerSockets[0]->send(receivedPacket, *mPlayerSockets[i]);
			break;
		}

		SDL_Delay(mRecvFrequency);
	}
}

// Funci�n que tienen los clientes (se encuentra en un hilo)
// Se encarga de recibir los paquetes del servidor
void NetworkManager::updateClient()
{
	Packet receivedPacket;
	Socket* clientSocket;

	while (!mExitThread) {
		// Receive info from server
		int success = mPlayerSockets[mClientId]->recv(receivedPacket, clientSocket);
        if (success < 0) continue;

		switch (receivedPacket.type)
		{
		case PACKETTYPE_CREATEPLAYER:
		{
			int newPlayerId = receivedPacket.info.createPlayer.newPlayerId;
			strcpy(gameManager()->playerNames[newPlayerId], receivedPacket.info.createPlayer.newPlayerName);

			//Update textures
			string entName = "Player" + to_string(newPlayerId + 1) + "Text";
			string newName = gameManager()->playerNames[newPlayerId];

			SDL_Color color = {255,255,255,255};
			sceneManager().getActiveScene()->findEntity(entName).get()
				->getComponent<Text>("text")->setText(newName, color);
		}
			break;
		case PACKETTYPE_START:
			sceneManager().change(new Battle(getNumberConnectedPlayers()));
			break;
		case PACKETTYPE_DISCONNECTIONREQUEST:
			// Borrar nombres de otros
			if (sceneManager().getActiveScene()->getName() == "ColorSelection"){
				strcpy(gameManager()->playerNames[receivedPacket.info.disconnectionRequest.playerId], " ");

				// Update texture
				string entName = "Player" + to_string(receivedPacket.info.disconnectionRequest.playerId + 1) + "Text";
				SDL_Color color = {255,255,255,255};
				sceneManager().getActiveScene()->findEntity(entName).get()
					->getComponent<Text>("text")->setText(" ", color);
			}
			break;
		case PACKETTYPE_SYNCSNAKE:
			//Actualizo la serpiente
			sceneManager().getActiveScene()->findEntity("Snake" + to_string(receivedPacket.info.snake.id)).get()->getComponent<Snake>("snake")
				->turn(Vector2(receivedPacket.info.snake.orientationX, receivedPacket.info.snake.orientationY));
			break;
		case PACKETTYPE_SYNCAPPLE:
			//Actualizo la manzana
			if(receivedPacket.info.apple.eaten){
				//Una serpiente se ha comido una manzana
				for(Apple& apple : sceneManager().getActiveScene()->findEntity("AppleGenerator").get()
					->getComponent<AppleGenerator>("applegenerator")->getApples())
					if(apple.posX == receivedPacket.info.apple.positionX && apple.posY == receivedPacket.info.apple.positionY)
						sceneManager().getActiveScene()->findEntity("Snake" + to_string(receivedPacket.info.apple.snakeId)).get()
							->getComponent<Snake>("snake")->eatApple(apple);
			}
			else
				//Se ha generado una manzana
				sceneManager().getActiveScene()->findEntity("AppleGenerator").get()
					->getComponent<AppleGenerator>("applegenerator")
					->generateApple(Vector2(receivedPacket.info.apple.positionX, receivedPacket.info.apple.positionY));
			break;
		}
		
		SDL_Delay(mClientFrequency);
	}
}

void NetworkManager::update() // HILO PARA SINCRONIZAR ESTADO DE JUEGO (lo tienen los 2 jugadores)
{
	if (mGameStarted) {
		if (mLastUpdate + mUpdateTime > sdlutils().currRealTime()) { // Cada 200 ms
			return;
		}

		mLastUpdate = sdlutils().currRealTime();
	}
}

void NetworkManager::close()
{
	mExitThread = true;

	if (mHost) { // si se es host, tienes que mandar a todo el mundo que te has desconectado

		Packet packet;

		// packet.type = PACKETTYPE_QUIT;

		// for (int i = 1; i < mPlayerSockets.size(); i++) // empezamos en 1 porque el 0 eres t� mismo
		// 	mPlayerSockets[0]->send(packet, *mPlayerSockets[i]);

		delete accept_t;
		delete receiveplayers_t;
	}
	else {
		Packet sendPacket;
		sendPacket.type = PACKETTYPE_DISCONNECTIONREQUEST;
		sendPacket.info.disconnectionRequest.playerId = gameManager()->myId;

		mPlayerSockets[gameManager()->myId]->send(sendPacket, *mPlayerSockets[0]);

		// updateclient_t->join();
		delete updateclient_t;
	}

	for(int i = 0; i < mPlayerSockets.size(); i++)
		if(mPlayerSockets[i] != nullptr){
			delete mPlayerSockets[i];
			mPlayerSockets[i] = nullptr;
		}
}

int NetworkManager::getNextPlayerId()
{
	for(int i = 0; i < mPlayerSockets.size(); i++)
		if(mPlayerSockets[i] == nullptr)
			return i;

	return -1;
}

void NetworkManager::sendStartGame() {
	// Lo manda el servidor al cliente para que empiece la partida
	startGameTimer();

	Packet packet; 

	packet.type = PACKETTYPE_START;

	for (int i = 1; i < mPlayerSockets.size(); i++)
		if (mPlayerSockets[i] != nullptr)
			mPlayerSockets[0]->send(packet, *mPlayerSockets[i]);
}

void NetworkManager::startGameTimer() {
	mGameStarted = true;
	mLastUpdate = SDL_GetTicks();
}

int NetworkManager::getClientId() {
	return mClientId;
}

int NetworkManager::getNumberConnectedPlayers() {
	int connectedPlayers = 0;

	for(int i = 0; i < mPlayerSockets.size(); i++)
		if(mPlayerSockets[i] != nullptr)
			connectedPlayers++;

	return connectedPlayers;
}

void NetworkManager::syncSnake(int id, Vector2 newOrientation)
{
	Packet packet;
	packet.type = PACKETTYPE_SYNCSNAKE;
	packet.info.snake.id = id;
	packet.info.snake.orientationX = newOrientation.x;
	packet.info.snake.orientationY = newOrientation.y;

	if (mHost){
		for (int i = 1; i < mPlayerSockets.size(); i++)
			if (mPlayerSockets[i] != nullptr)
				mPlayerSockets[0]->send(packet, *mPlayerSockets[i]);
	}
	else 
		mPlayerSockets[mClientId]->send(packet, *mPlayerSockets[0]);
}

void NetworkManager::syncApple(int id, Vector2 position, bool eaten)
{
	Packet packet;
	packet.type = PACKETTYPE_SYNCAPPLE;
	packet.info.apple.snakeId = id;
	packet.info.apple.positionX = position.x;
	packet.info.apple.positionY = position.y;
	packet.info.apple.eaten = eaten;

	if (mHost)
		for (int i = 1; i < mPlayerSockets.size(); i++)
			if (mPlayerSockets[i] != nullptr)
				mPlayerSockets[0]->send(packet, *mPlayerSockets[i]);
	else
		mPlayerSockets[mClientId]->send(packet, *mPlayerSockets[0]);
}

void NetworkManager::sendFinishGame()
{
}