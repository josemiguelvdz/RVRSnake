#pragma once

#ifndef __ENTITYCOMPONENT_GAMEMANAGER
#define __ENTITYCOMPONENT_GAMEMANAGER

#include "Component.h"
#include <string>

class GameManager : public Component
{
    static GameManager* MInstance;

public:
	GameManager& operator=(const GameManager& o) = delete;
	GameManager();
	GameManager(const GameManager& o) = delete;
	~GameManager() override;

    static GameManager* Instance();

	void start() override;

    std::string mPlayerName;
};

/**
This macro defines a compact way for using the singleton GameManager, instead of
writing GameManager::instance()->method() we write gameManager()->method()
*/
inline GameManager* gameManager() {
	return GameManager::Instance();
}
#endif