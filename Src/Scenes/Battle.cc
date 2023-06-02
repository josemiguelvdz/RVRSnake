#include "Battle.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Board.h"
#include "../EntityComponent/Components/Snake.h"
#include "../EntityComponent/Components/AppleGenerator.h"
#include "../EntityComponent/Components/GameManager.h"

#include <iostream>

Battle::Battle(int snakeNumber) : Scene("Battle")
{
	/*
		TABLERO
	*/
	auto board = addEntity("Board");
	board.get()->addComponent(new Board());

	/*
		SNAKES
	*/

	for(int i = 0; i < snakeNumber; i++){
		auto snake = addEntity("Snake" + std::to_string(i));
		
		Vector2 position, orientation;
		position.x = i < (MAX_PLAYERS + 1) / 2 ? 4 : 21 - 4;
		position.y = i % 2 == 0 ? 3 : 21 - 3;

		orientation.x = i < (MAX_PLAYERS + 1) / 2? 1 : -1;
		orientation.y = 0;

		snake.get()->addComponent(new Snake(i, position, orientation));
		snake.get()->setDepth(2);
	}

	/*
		MANZANA GENERATOR
	*/
	auto appleGenerator = addEntity("AppleGenerator");
	appleGenerator.get()->addComponent(new AppleGenerator());
	appleGenerator.get()->setDepth(1);

	/*
		GAME MANAGER
	*/
	auto gameManager = addEntity("GameManager");
	gameManager.get()->addComponent(new GameManager());
}

Battle::~Battle(){
}