#include "GameManager.h"

#include "../../Scenes/Scene.h"
#include "../../Scenes/SceneManager.h"
#include "../Entity.h"

#include <iostream>

GameManager* GameManager::MInstance = nullptr;

GameManager::GameManager(){
	mName = "gameManager";
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

	mPlayerName = "Snake";
}

GameManager* GameManager::Instance()
{
	return MInstance;
}