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

	// for(int i = 0; i < snakeNumber; i++){
	// 	auto snake = addEntity("Snake" + std::to_string(i));;
		
	// 	snake.get()->addComponent(new Snake(i));
	// }

	/*
		MANZANA GENERATOR
	*/
	auto appleGenerator = addEntity("AppleGenerator");
	appleGenerator.get()->addComponent(new AppleGenerator());
	
}

Battle::~Battle(){
}