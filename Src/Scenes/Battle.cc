#include "Battle.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Board.h"
#include "../EntityComponent/Components/Snake.h"
#include "../EntityComponent/Components/AppleGenerator.h"

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
		snake.get()->addComponent(new Snake(i, {4, 3}, {1, 0}));
		snake.get()->setDepth(2);
	}

	/*
		MANZANA GENERATOR
	*/
	auto appleGenerator = addEntity("AppleGenerator");
	appleGenerator.get()->addComponent(new AppleGenerator());
	appleGenerator.get()->setDepth(1);
	
}

Battle::~Battle(){
}