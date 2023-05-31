#pragma once

#ifndef __ENTITYCOMPONENT_SNAKE
#define __ENTITYCOMPONENT_SNAKE

#include "Component.h"
#include "../../Utils/Vector2.h"
#include <string>
#include <list>

class SnakePart;
class SDL_Texture;

#define STARTING_LENGTH 3

class Snake : public Component
{
	std::string mName;

	std::list<SnakePart*> mParts;

	int mId;
	Vector2 mPosition, mOrientation;

	float mSpeed;

public:
	Snake(int id, Vector2 position, Vector2 orientation);
	~Snake();

	void start() override;
	
	void update(const double& dt) override;

	void render() override;

	/**
	 Set name to mesh (renderMesh in rendermanager array).
		@param name: name for map and for entity that attached in node
	*/

	void setName(std::string name);

	/**
	Set it is static entity or not
	*/
	std::string getName();
};
#endif