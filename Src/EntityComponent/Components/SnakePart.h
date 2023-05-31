#pragma once

#ifndef __ENTITYCOMPONENT_SNAKEPART
#define __ENTITYCOMPONENT_SNAKEPART

#include "../../Utils/Vector2.h"
#include "../../Utils/macros.h"

#include <string>
#include <unordered_map>

#define BOX_SIZE 32

class SDL_Texture;

enum SnakePartType { SNAKEPARTTYPE_HEAD, SNAKEPARTTYPE_BODY, SNAKEPARTTYPE_CORNER, SNAKEPARTTYPE_TAIL };

class SnakePart
{
	int mId;
	Vector2 mPosition, mOrientation;

	std::unordered_map<SnakePartType, SDL_Rect> mTextureClips;

public:
	SnakePart(int id, Vector2 position, Vector2 orientation);
	~SnakePart();

	void update(const double& dt, float speed);
	void render(SnakePart* next);
};
#endif