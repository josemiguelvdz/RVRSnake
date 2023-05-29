#include "Battle.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Board.h"
#include "../EntityComponent/Components/Snake.h"

#include <iostream>

Battle::Battle(int snakeNumber) : Scene("Battle")
{
	auto board = addEntity("Board");

	board.get()->addComponent(new Board());

	// for(int i = 0; i < snakeNumber; i++){
	// 	auto snake = addEntity("Snake" + std::to_string(i));;
		
	// 	snake.get()->addComponent(new Snake(i));
	// }
}