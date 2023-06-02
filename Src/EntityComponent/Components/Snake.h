#pragma once

#ifndef __ENTITYCOMPONENT_SNAKE
#define __ENTITYCOMPONENT_SNAKE

#include "Component.h"
#include "AppleGenerator.h"
#include "../../Utils/Vector2.h"
#include <string>
#include <list>

class SnakePart;
class SDL_Texture;

#define STARTING_LENGTH 3

class Snake : public Component
{
	std::list<SnakePart*> mParts;

	uint8_t mId;
	Vector2 mPosition, mOrientation;
	Vector2 mNextPosition, mNextOrientation;

	std::string mTextureName;

	float mSpeed, mSpeedIncrement;

	bool mAlive;
	bool mTurnNextPartToCorner;

	AppleGenerator* mAppleGenerator;

	Timer* mTimer = nullptr;

	Vector2 snap();
	float snapX();
	float snapY();

	void move();
	void turn(Vector2 newOrientation);

	void bringLastPartFirst();

	//Comprueba si hay una manzana en esa casilla
	bool eat();
	//Aumenta en 1 el tamaño de la serpiente
	void eatApple(Apple& apple);

	bool outOfBounds(int rightEdge, int bottomEdge);
	bool hit();

public:
	Snake(int id, Vector2 position, Vector2 orientation, std::string texture = "snake");
	~Snake();

	void start() override;
	
	void update(const double& dt) override;

	void render() override;

	std::list<SnakePart*> getParts();

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