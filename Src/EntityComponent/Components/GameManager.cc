#include "GameManager.h"

#include "../../Scenes/Scene.h"
#include "../../Scenes/SceneManager.h"
#include "../Entity.h"

GameManager* GameManager::MInstance = nullptr;

GameManager::GameManager(){

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

	mName = "Snake";
}

GameManager* GameManager::Instance()
{
	return MInstance;
}