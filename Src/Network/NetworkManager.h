#pragma once
#include "../Utils/Singleton.h"
#include "Socket.h"
#include "../Utils/Vector2.h"

#include <vector>
#include <string>
#include <thread>

#define LOOPBACK "127.0.0.1"
#define MULTISNAKE_PORT "2300"

class NetworkManager : public Singleton<NetworkManager>
{
	friend Singleton<NetworkManager>;

	std::vector<Socket*> mPlayerSockets;

	// SERVER

	std::thread* accept_t;
	std::thread* receiveplayers_t;
	std::thread* sendplayers_t;

	void acceptPlayers();
	void receivePlayers();

	// CLIENT

	uint8_t mClientId;

	std::thread* updateclient_t;

	void updateClient();

	// VARIABLES

	bool mExitThread;
	bool mGameStarted;

	_Float32 mAcceptFrequency;
	_Float32 mSendFrequency;
	_Float32 mRecvFrequency;

	_Float32 mClientFrequency;

	// Timer
	uint32_t mLastUpdate; //tiempo desde el �ltimo update
	uint32_t mUpdateTime = 150; //los segundos que tarda en actualizarse el reloj

	// Host
	bool mHost;

	bool mInitialized;

	/**
	@return The index of the first gap in the player array. If there are none, return -1.
	*/
	int getNextPlayerId();

	NetworkManager();

public:
	~NetworkManager() override;

	// Funci�n que inicializa SDL_Net y tu funci�n (servidor o cliente)
	bool init(bool host, const char* ipAddress = nullptr);
	void update();

	void close();

	bool isHost() { return mHost; }
	bool initialized() { return mInitialized; };

	void startGameTimer();

	void sendStartGame();
	void sendFinishGame();

	void syncSnake(int id, Vector2 position, Vector2 orientation, bool alive, bool ate, bool turnNextPartToCorner);
	void syncApple(int id, Vector2 position, bool eaten);

	void setGameStarted(bool gameStarted_) { mGameStarted = gameStarted_; }

	int getClientId();
	int getNumberConnectedPlayers();
};

inline NetworkManager& networkManager() {
    return *NetworkManager::Instance();
}