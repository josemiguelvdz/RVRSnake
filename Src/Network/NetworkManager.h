#pragma once
#include "Socket.h"
#include "../Utils/Singleton.h"
#include "../Utils/Vector2.h"

#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>

class Game;
class Player;

typedef struct {
    char* host;
    char* port;
} IPaddress;

class NetworkManager : public Singleton<NetworkManager>
{
	friend Singleton<NetworkManager>;

	std::vector<Socket> mPlayerSockets;
	std::vector<IPaddress> mPlayerIps;
	std::vector<int> mPlayerIds;

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

	uint8_t getClientID(const IPaddress& addr);

	bool compareAddress(const IPaddress& addr1, const IPaddress& addr2);

	// VARIABLES

	char mType; // 'h' para host y 'c' para client

	const int MAX_PLAYERS = 15;

	uint8_t mIdCount;
	uint8_t maxIdCount;
	Game* mGame;

	bool mExitThread;
	bool mGameStarted;

	std::string mMyName;
	std::string mOtherName;

	// For clients ip=server_address, for host ip=local_address
	IPaddress mIp;

	// For clients socket=socket_server, for host socket=local_socket
	Socket mSocket;

	_Float32 mAcceptFrequency;
	_Float32 mSendFrequency;
	_Float32 mRecvFrequency;

	_Float32 mClientFrequency;

	// Timer
	uint32_t mLastUpdate; //tiempo desde el �ltimo update
	uint32_t mUpdateTime = 150; //los segundos que tarda en actualizarse el reloj

	// Host
	bool mHost;

	NetworkManager(Game* game_);

public:
	~NetworkManager();

	bool init(char type, const char* ip_addr = nullptr, std::string name = "");
	void update();

	void close();

	bool isHost() { return mHost; }

	std::string getOtherName() { return mOtherName;}
	std::string getMyName() { return mMyName; }

	void startGameTimer();

	void sendStartGame();
	void sendFinishGame();

	void syncSnake();
	void syncApple();

	void setGameStarted(bool gameStarted_) { mGameStarted = gameStarted_; }

	int getIdCount() { return mIdCount; };
	int getMaxIdCount() { return maxIdCount; };
	void setMaxIdCount(int id) { maxIdCount = id; };
};

inline NetworkManager& networkManager() {
    return *NetworkManager::Instance();
}