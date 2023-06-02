#pragma once
#include "../Utils/Singleton.h"
#include "Socket.h"
#include "../Utils/Vector2.h"

#include <vector>
#include <string>
#include <thread>

#define LOOPBACK "127.0.0.1"
#define MULTISNAKE_PORT "2300"

// typedef struct {
//     char* host;
//     char* port;
// } IPaddress;

class NetworkManager : public Singleton<NetworkManager>
{
	friend Singleton<NetworkManager>;

	std::vector<Socket*> mPlayerSockets;
	//std::vector<IPaddress> mPlayerIps;
	//std::vector<int> mPlayerIds;

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

	// UTILS

	// uint8_t getClientID(const IPaddress& addr);

	// bool compareAddress(const IPaddress& addr1, const IPaddress& addr2);

	// VARIABLES

	//char mType; // 'h' para host y 'c' para client

	// uint8_t mIdCount;
	// uint8_t maxIdCount;

	bool mExitThread;
	bool mGameStarted;

	// For clients ip=server_address, for host ip=local_address
	//IPaddress mIp;

	// For clients socket=socket_server, for host socket=local_socket
	//Socket mSocket;

	_Float32 mAcceptFrequency;
	_Float32 mSendFrequency;
	_Float32 mRecvFrequency;

	_Float32 mClientFrequency;

	// Timer
	uint32_t mLastUpdate; //tiempo desde el �ltimo update
	uint32_t mUpdateTime = 150; //los segundos que tarda en actualizarse el reloj

	// Host
	bool mHost;

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

	void startGameTimer();

	void sendStartGame();
	void sendFinishGame();

	void syncSnake();
	void syncApple();

	void setGameStarted(bool gameStarted_) { mGameStarted = gameStarted_; }

	int getClientId();

	// int getIdCount() { return mIdCount; };
	// int getMaxIdCount() { return maxIdCount; };
	// void setMaxIdCount(int id) { maxIdCount = id; };
};

inline NetworkManager& networkManager() {
    return *NetworkManager::Instance();
}