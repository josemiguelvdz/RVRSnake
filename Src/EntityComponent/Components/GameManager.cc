#include "GameManager.h"

#include "../../Scenes/Scene.h"
#include "../../Scenes/SceneManager.h"
#include "../Entity.h"

#include <iostream>

GameManager* GameManager::MInstance = nullptr;

GameManager::GameManager(){
	mName = "gameManager";

	myName = " Snake";

	for(int i = 0; i < MAX_PLAYERS; i++)
		playerColors[i] = SNAKECOLOR_GRAY;

	playerColorTextureNames[SNAKECOLOR_RED] = "redSnake";
	playerColorTextureNames[SNAKECOLOR_BLUE] = "blueSnake";
	playerColorTextureNames[SNAKECOLOR_YELLOW] = "yellowSnake";
	playerColorTextureNames[SNAKECOLOR_PURPLE] = "purpleSnake";
	playerColorTextureNames[SNAKECOLOR_GRAY] = "snake";
}

GameManager::~GameManager(){
    
}

void GameManager::start() {
    if (MInstance != nullptr)
		sceneManager().getActiveScene()->removeEntity(mEntity->getName());
	else {
		MInstance = this;
		sceneManager().getActiveScene()->promoteToGlobal(mEntity);
	}
}

GameManager* GameManager::Instance()
{
	return MInstance;
}