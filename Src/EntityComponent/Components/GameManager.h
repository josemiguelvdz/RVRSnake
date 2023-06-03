#pragma once

#ifndef __ENTITYCOMPONENT_GAMEMANAGER
#define __ENTITYCOMPONENT_GAMEMANAGER

#include "Component.h"
#include <string>
#include <unordered_map>

#define MAX_PLAYERS 4

enum SnakeColor : uint8_t { SNAKECOLOR_RED, SNAKECOLOR_BLUE, SNAKECOLOR_YELLOW, SNAKECOLOR_PURPLE, SNAKECOLOR_GRAY };

class GameManager : public Component
{
    static GameManager* MInstance;

public:
	GameManager& operator=(const GameManager& o) = delete;
	GameManager();
	GameManager(const GameManager& o) = delete;
	~GameManager() override;

    static GameManager* Instance();

	int getAliveSnakes();

	void start() override;
	void update(const double& dt) override;

    std::string myName;
	uint8_t myId;

	char playerNames[MAX_PLAYERS][8];
	SnakeColor playerColors[MAX_PLAYERS];
	std::unordered_map<SnakeColor, std::string> playerColorTextureNames;
};

/**
This macro defines a compact way for using the singleton GameManager, instead of
writing GameManager::instance()->method() we write gameManager()->method()
*/
inline GameManager* gameManager() {
	return GameManager::Instance();
}
#endif