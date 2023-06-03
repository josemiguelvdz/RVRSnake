#include "GameManager.h"

#include "../../Scenes/Scene.h"
#include "../../Scenes/TitleScreen.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/ColorSelection.h"

#include "Snake.h"
#include "../Entity.h"
#include "../../Network/NetworkManager.h"

#include <iostream>
#include <string>

GameManager* GameManager::MInstance = nullptr;

GameManager::GameManager(){
	mName = "gameManager";

	myName = " Snake";

	playerColors[0] = SNAKECOLOR_RED;
	playerColors[1] = SNAKECOLOR_BLUE;
	playerColors[2] = SNAKECOLOR_YELLOW;
	playerColors[3] = SNAKECOLOR_PURPLE;

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

void GameManager::update(const double& dt){
	std::cout << getAliveSnakes() << "\n";
	if (!networkManager().initialized()){
		std::cout << getAliveSnakes() << "\n";
		if (getAliveSnakes() == 0){
			// CHANGE TO TITLE SCREEN
			sceneManager().change(new TitleScreen());
		}
	}
	else {
		if (networkManager().isHost() && getAliveSnakes() == 1){
			// SEND PACKET TO COLOR SELECTION
			networkManager().sendFinishGame();

			// CHANGE TO COLOR SELECTION
			std::vector<string> names(4, " ");
			names[0] = playerNames[0];
			names[1] = playerNames[1];
			names[2] = playerNames[2];
			names[3] = playerNames[3];

			std::vector<int> colors(4, -1);
			colors[0] = playerColors[0];
			colors[1] = playerColors[1];
			colors[2] = playerColors[2];
			colors[3] = playerColors[3];

			Scene* colorSelection = new ColorSelection(names, colors, true);
			sceneManager().change(colorSelection);
		}
	}
}

int GameManager::getAliveSnakes() {
	
	int cont = 0;
	for (int i = 0; i < MAX_PLAYERS; i++){
		Entity* snake = sceneManager().getActiveScene()->findEntity("Snake" + std::to_string(i)).get();
		if (snake != nullptr && snake->getComponent<Snake>("snake")->isAlive())
			cont++;
	}

	return cont;
}

GameManager* GameManager::Instance()
{
	return MInstance;
}