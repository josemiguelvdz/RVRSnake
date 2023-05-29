#pragma once

#ifndef __ENTITYCOMPONENT_SNAKEPART
#define __ENTITYCOMPONENT_SNAKEPART

#include "../../Utils/Vector2.h"

#include <string>
#include <vector>

class SDL_Texture;

class SnakePart
{
	int id;
	Vector2 position;

public:
	SnakePart(int id);
	~SnakePart();
};
#endif