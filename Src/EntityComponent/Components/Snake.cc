#include "Snake.h"
#include "SnakePart.h"
#include "../Entity.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"

#include <iostream>

using namespace std;

Snake::Snake(int id, Vector2 position, Vector2 orientation) : mName("snake"), mId(id), 
	mPosition(position * BOX_SIZE), mOrientation(orientation * BOX_SIZE)
{
	mSpeed = 5.0f;
	mAlive = true;
	distanceSinceCorner = BOX_SIZE;
	gridOffset = 0;
	lastGridPosition = mPosition;
	turnNextPartToCorner = false;
}

Snake::~Snake()
{
}

void Snake::start()
{
    for (int i = 1; i < STARTING_LENGTH; i++)
        mParts.push_back(new SnakePart(mId, mPosition - mOrientation * i, mOrientation));
}

void Snake::update(const double& dt)
{
	if(!mAlive)
		return;

	if(distanceSinceCorner >= BOX_SIZE){
		//No se puede ir en tu direccion actual ni en la opuesta
		//Solo se permiten giros de 90 grados

		if (abs(mOrientation.x) < .1f && inputManager().getAxis("horizontal") > .1f)
			turn({ BOX_SIZE, 0 }); //Derecha
		else if (abs(mOrientation.x) < .1f && inputManager().getAxis("horizontal") < -.1f)
			turn({ -BOX_SIZE, 0 }); //Izquierda
		else if (abs(mOrientation.y) < .1f && inputManager().getAxis("vertical") > .1f)
			turn({ 0, -BOX_SIZE }); //Arriba
		else if (abs(mOrientation.y) < .1f && inputManager().getAxis("vertical") < -.1f)
			turn({ 0, BOX_SIZE }); //Abajo
	}

	mPosition = mPosition + mOrientation * (float) (mSpeed * dt);

	gridOffset += mSpeed * dt * BOX_SIZE;
	distanceSinceCorner += mSpeed * dt * BOX_SIZE;

	for(auto part : mParts)
		part->update(dt, mSpeed);

	if (gridOffset > BOX_SIZE){
		bringLastPartFirst();

		if(turnNextPartToCorner){
			turnNextPartToCorner = false;
			mParts.front()->setCorner();
		}
	}

	//if(isOutOfBounds())
	//	mAlive = false;
}

void Snake::render()
{
	auto part = mParts.begin();
	auto nextPart = ++mParts.begin();

	for(int i = 0; i < mParts.size(); i++, part++, nextPart++)
		(*part)->render(nextPart == mParts.end() ? nullptr : *nextPart);

	auto bgTexture = &sdlutils().images().at("snakeTexture");

	//Cabeza viva o muerta
    SDL_Rect clipBox = build_sdlrect(2 * BOX_SIZE, mAlive ? 0 : 1 * BOX_SIZE, 1 * BOX_SIZE , 1 * BOX_SIZE);
    
    SDL_Rect textureBox = build_sdlrect(lastGridPosition.x, lastGridPosition.y, 1 * BOX_SIZE, 1 * BOX_SIZE);

	Vector2 orientation = mOrientation;
	if (turnNextPartToCorner)
		orientation = mParts.front()->getOrientation();

 	float rotationAngle = 0;    	//Derecha
    if (orientation.x < -.1f)		//Izquierda
        rotationAngle = 180;
    else if (orientation.y > .1f)	//Abajo
        rotationAngle = 90;     
    else if (orientation.y < -.1f) //Arriba
        rotationAngle = 270;

 	bgTexture->render(clipBox, textureBox, rotationAngle, nullptr);
}

string Snake::getName()
{
	return mName;
}

void Snake::setName(string name)
{
	mName = name;
}

void Snake::turn(Vector2 newOrientation)
{
	mPosition = snap();
	distanceSinceCorner = 0;
	gridOffset = 0;

	if(mPosition.distance(mParts.front()->getPosition()) > BOX_SIZE)
		bringLastPartFirst();

	mOrientation = newOrientation;
	turnNextPartToCorner = true;
	lastGridPosition = mPosition;
}

void Snake::bringLastPartFirst()
{
	gridOffset = 0;

	auto tail = mParts.back();
	mParts.pop_back();
	tail->setPositionAndOrientation(lastGridPosition, mOrientation);
	mParts.push_front(tail);

	lastGridPosition = snap();
}

Vector2 Snake::snap() {
	return Vector2(snapX(), snapY());
}

float Snake::snapX()
{
    int xPosition = mPosition.x / BOX_SIZE;
	float xOffset = mPosition.x / BOX_SIZE - xPosition;

	if(xOffset < .5f)
		return xPosition * BOX_SIZE;
	else
		return (xPosition + 1) * BOX_SIZE;
}

float Snake::snapY()
{
    int yPosition = mPosition.y / BOX_SIZE;
	float yOffset = mPosition.y / BOX_SIZE - yPosition;

	if(yOffset < .5f)
		return yPosition * BOX_SIZE;
	else
		return (yPosition + 1) * BOX_SIZE;
}