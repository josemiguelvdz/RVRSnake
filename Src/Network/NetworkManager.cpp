#include "NetworkManager.h"
#include "Packet.h"

#include "../Utils/SDLUtils.h"

#include <SDL2/SDL.h>

using namespace std;

// SERVIDOR

// Funci�n que se encarga de aceptar a los jugadores (se encuentra en un hilo)

void NetworkManager::acceptPlayers()
{
	while (!mExitThread) {
		Packet receivedPacket;
		Socket* clientSocket;

		int success = mSocket.recv(receivedPacket, clientSocket);
        if (success < 0) continue;

		// if(receivedPacket == PACKETTYPE_) {

		// }


		//CODIGO DE PAELLA, BORRAR LUEGO  ------------------------------------------------------------- <<<----- <<<----- !!!!
		// string* remoteIP;

		// if ((remoteIP = SDLNet_TCP_GetPeerAddress(clientSocket)))
		// 	std::cout << ("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port)) << std::endl;
		// else
		// 	std::cout << ("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError()) << std::endl;

		// int id = getClientID(*remoteIP);

		// Packet pkt;
		// pkt.packet_type = EPT_ACCEPT;

		// strcpy_s(pkt.accept.player_name, mMyName.c_str());
		// sdlutils().soundEffects().at("connected").play();

		// if (mPlayerSockets.size() > MAX_PLAYERS) { // TODO: CHECK IF A PLAYER IS DISCONNECTED
		// 	pkt.packet_type = EPT_DENY;
		// }
		// else {
		// 	if (id == -1) {
		// 		id = mIdCount;

		// 		mPlayerIps.push_back(*remoteIP); // Como eres nuevo, se mete tu IP en el vector
		// 	}

		// 	mPlayerSockets.push_back(clientSocket); // Se mete tu socket en el vector
		// }

		// pkt.accept.player_id = id;

		// if (SDLNet_TCP_Send(clientSocket, &pkt, sizeof(Packet)) < sizeof(Packet))
		// {
		// 	std::cout << ("SDLNet_TCP_Send: %s\n", SDLNet_GetError()) << std::endl;
		// 	exit(EXIT_FAILURE);
		// }

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
		for (int i = 1u; i < mPlayerSockets.size(); i++) { // Comenzamos en uno porque el 0 somos nosotros mismos
			int success = mSocket.recv(receivedPacket, clientSocket);
        	if (success < 0) continue;

			switch (receivedPacket.packetType) {
			case PACKETTYPE_NAME:
				break;
			case PACKETTYPE_QUIT:
				break;
			}	

			SDL_Delay(mRecvFrequency);
		}
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
		int success = mSocket.recv(receivedPacket, clientSocket);
        if (success < 0) continue;

			Player* p = nullptr;

		switch (receivedPacket.packetType)
		{
		case PACKETTYPE_START:
			// Start game
			// mGame->sendMessageScene(new Jornada(mGame, "Jornada" + to_string(server_pkt.startGame.num_jornada + 1), server_pkt.startGame.num_jornada, false));
			// startGameTimer();
			break;
		}

		SDL_Delay(mClientFrequency);
	}
}

// Funci�n para asignar IDs
uint8_t NetworkManager::getClientID(const IPaddress& addr)
{
	int id = -1;

	for (int i = 0u; i < mPlayerIps.size(); i++) {
		if (compareAddress(mPlayerIps[i], addr)) {
			id = i;
			break;
		}
	}

	return id;
}

bool NetworkManager::compareAddress(const IPaddress& addr1, const IPaddress& addr2)
{
	return strcmp(addr1.host, addr2.host) && strcmp(addr1.port, addr2.port);
}

NetworkManager::NetworkManager() : mSocket("127.0.0.1", "3000")
{
	mExitThread = false;
	mGameStarted = false;

	mType = '0';
	mIdCount = 0;

	mAcceptFrequency = 150;
	mRecvFrequency = 50;
	mSendFrequency = 100;

	mClientFrequency = 50;
}

NetworkManager::~NetworkManager()
{
	// SDLNet_TCP_Close(socket);
	// SDLNet_Quit();
}

// Funci�n que inicializa SDL_Net y tu funci�n (servidor o cliente)

bool NetworkManager::init(char type, const char* ip_addr, std::string name)
{
	//SDL NET Init

	mType = type;
	

	//SDL NET ResolveHost

	//SDL NET TCP Open
	
	mMyName = name;
	
	Packet receivedPacket;

	if (mType == 'c') { // Si somos un cliente
		mHost = false;

		Socket* clientSocket;

		while (receivedPacket.packetType == PACKETTYPE_ACCEPT || receivedPacket.packetType == PACKETTYPE_DENY)
			while (mSocket.recv(receivedPacket, clientSocket) < 0) {}

		if (receivedPacket.packetType == PACKETTYPE_ACCEPT) { // Cuando nos acepte
			// recv info
			mOtherName = receivedPacket.packetInfo.accept.playerName;

			// Mandarle el nombre
			// Send info
			// Packet namePkt;
			// namePkt.packet_type = EPT_NAME;

			// strcpy_s(namePkt.name.player_name, mMyName.c_str());

			// if (SDLNet_TCP_Send(socket, &namePkt, sizeof(Packet)) < sizeof(Packet))
			// {
			// 	std::cout << ("SDLNet_TCP_Send: %s\n", SDLNet_GetError()) << std::endl;
			// 	exit(EXIT_FAILURE);
			// }

			// updateclient_t = new std::thread(&NetworkManager::updateClient, this);
		}
		else if (receivedPacket.packetType == PACKETTYPE_DENY) // Si nos rechazan porque la partida est� llena
			return false;
	}
	else { // Si somos un host
		mHost = true;
		
		// Hilos
		accept_t = new std::thread(&NetworkManager::acceptPlayers, this);
		receiveplayers_t = new std::thread(&NetworkManager::receivePlayers, this);

		mPlayerSockets.push_back(mSocket);
		mPlayerIps.push_back(mIp);

		mClientId = 0;
	}

	return true;
}


void NetworkManager::update() // HILO PARA SINCRONIZAR ESTADO DE JUEGO (lo tienen los 2 jugadores)
{
	if (mGameStarted) {
		if (mLastUpdate + mUpdateTime > sdlutils().currRealTime()) { // Cada 200 ms
			return;
		}

		mLastUpdate = sdlutils().currRealTime();

		// Sync Players
		syncSnake();
	}
}

void NetworkManager::close()
{
	mExitThread = true;

	if (mType == 'h') { // si se es host, tienes que mandar a todo el mundo que te has desconectado

		Packet packet;

		packet.packetType = PACKETTYPE_QUIT;

		for (int i = 1u; i < mPlayerSockets.size(); i++) // empezamos en 1 porque el 0 eres t� mismo
			if (mSocket.send(packet, mPlayerSockets[i]) == -1)
			{
				std::cout << "Quit package send error\n";
				exit(EXIT_FAILURE);
			}

		accept_t->join();
		receiveplayers_t->join();

		delete accept_t;
		delete receiveplayers_t;
	}
	else if (mType == 'c') {

		Packet packet;

		packet.packetType = PACKETTYPE_QUIT;

		if (mSocket.send(packet, mSocket) == -1) //??????? ------------ !!! !! ?
		{
			std::cout << "Quit package send error\n";
			exit(EXIT_FAILURE);
		}

		updateclient_t->join();
		delete updateclient_t;
	}

	mPlayerIds.clear();
	mPlayerIps.clear();
	mPlayerSockets.clear();
	
	//SDLNet_TCP_Close(socket);
}

void NetworkManager::sendStartGame() {
	// Lo manda el servidor al cliente para que empiece la partida
	startGameTimer();

}

void NetworkManager::startGameTimer() {
	mGameStarted = true;
	mLastUpdate = SDL_GetTicks();
}

void NetworkManager::syncSnake()
{
}

void NetworkManager::syncApple()
{
}

void NetworkManager::sendFinishGame()
{
}