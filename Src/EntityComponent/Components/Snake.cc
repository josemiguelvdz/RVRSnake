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

	if(distanceSinceCorner >= BOX_SIZE / 2){
		//No se puede ir en tu direccion actual ni en la opuesta
		//Solo se permiten giros de 90 grados

		if (abs(mOrientation.x) < .1f && inputManager().getAxis("horizontal") > .1f){
			mOrientation = { BOX_SIZE, 0 }; //Derecha
			snap();
			distanceSinceCorner = 0;
		}
		else if (abs(mOrientation.x) < .1f && inputManager().getAxis("horizontal") < -.1f){
			mOrientation = { -BOX_SIZE, 0 }; //Izquierda
			snap();
			distanceSinceCorner = 0;
		}
		else if (abs(mOrientation.y) < .1f && inputManager().getAxis("vertical") > .1f){
			mOrientation = { 0, -BOX_SIZE }; //Arriba
			snap();
			distanceSinceCorner = 0;
		}
		else if (abs(mOrientation.y) < .1f && inputManager().getAxis("vertical") < -.1f) {
			mOrientation = { 0, BOX_SIZE }; //Abajo
			snap();
			distanceSinceCorner = 0;
		}
	}
	
	mPosition = mPosition + mOrientation * (float) (mSpeed * dt);

	distanceSinceCorner += mSpeed * dt * BOX_SIZE;

	for(auto part : mParts)
		part->update(dt, mSpeed);

	//if(isOutOfBounds())
	//	mAlive = false;
}

void Snake::render()
{
	auto bgTexture = &sdlutils().images().at("snakeTexture");

	//Cabeza viva o muerta
    SDL_Rect clipBox = build_sdlrect(2 * BOX_SIZE, mAlive ? 1 * BOX_SIZE : 0, 1 * BOX_SIZE, 1 * BOX_SIZE);
    
    SDL_Rect textureBox = {mPosition.x, mPosition.y, 1 * BOX_SIZE, 1 * BOX_SIZE };

 	float rotationAngle = 0;    //Derecha
    if (mOrientation.x < -.1f)
        rotationAngle = 180;    //Izquierda
    else if (mOrientation.y > .1f)
        rotationAngle = 90;     //Abajo
    else if (mOrientation.y < -.1f)
        rotationAngle= 270;     //Arriba

 	bgTexture->render(clipBox, textureBox, rotationAngle, nullptr);

	auto part = mParts.begin();
	auto nextPart = ++mParts.begin();

	for(int i = 0; i < mParts.size(); i++, part++, nextPart++)
		(*part)->render(nextPart == mParts.end() ? nullptr : *nextPart);
}

string Snake::getName()
{
	return mName;
}

void Snake::setName(string name)
{
	mName = name;
}

void Snake::snap() {
	snapX();
	snapY();
}

void Snake::snapX()
{
    int xPosition = mPosition.x / BOX_SIZE;
	float xOffset = mPosition.x / BOX_SIZE - xPosition;

	cout << "pos.x : " << mPosition.x << "  xPos: " << xPosition << "  xOffset " << xOffset;

	if(xOffset < .5f)
		mPosition.x = xPosition * BOX_SIZE;
	else
		mPosition.x = (xPosition + 1) * BOX_SIZE;

	cout << "  newPos: " << mPosition.x << endl;
}

void Snake::snapY()
{
    int yPosition = mPosition.y / BOX_SIZE;
	float yOffset = mPosition.y / BOX_SIZE - yPosition;

	cout << "pos.y : " << mPosition.y << "  yPos: " << yPosition << "  yOffset " << yOffset;

	if(yOffset < .5f)
		mPosition.y = yPosition * BOX_SIZE;
	else
		mPosition.y = (yPosition + 1) * BOX_SIZE;

	cout << "  newPos: " << mPosition.y << endl;
}