#pragma once

#ifndef __ENTITYCOMPONENT_SNAKE
#define __ENTITYCOMPONENT_SNAKE

#include "Component.h"
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

public:
	Snake(int id);
	~Snake();

	void start() override;
	
	void update(const double& dt) override;

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