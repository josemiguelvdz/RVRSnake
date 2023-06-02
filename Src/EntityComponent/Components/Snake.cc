#include "Snake.h"
#include "SnakePart.h"
#include "GameManager.h"
#include "../Entity.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"
#include "../../Scenes/Scene.h"
#include "../../Utils/Timer.h"
#include "../../Network/NetworkManager.h"

#include <iostream>

using namespace std;

Snake::Snake(int id, Vector2 position, Vector2 orientation, string texture) : mId(id), 
	mPosition(position * BOX_SIZE), mOrientation(orientation * BOX_SIZE), mTextureName(texture)
{
	mSpeed = 4.0f;
	mSpeedIncrement = 0.2f;
	mAlive = true;
	mTurnNextPartToCorner = false;

	setName("snake");
}

Snake::~Snake()
{
}

void Snake::start()
{
	mAppleGenerator = mEntity->getScene()->findEntity("AppleGenerator").get()->getComponent<AppleGenerator>("applegenerator");

    for (int i = 1; i < STARTING_LENGTH; i++)
        mParts.push_back(new SnakePart(mId, mPosition - mOrientation * i, mOrientation, mTextureName));

	mNextPosition = mPosition + mOrientation;
	mNextOrientation = mOrientation;

	mTimer = new Timer();
}

void Snake::update(const double& dt)
{
	mTimer->update(dt);

	if(!mAlive)
		return;

	//Solo se puede controlar tu serpiente
	if(networkManager().getClientId() == mId){
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

	if(mTimer->getRawSeconds() >= 1 / mSpeed){
		mTimer->reset();

		if(outOfBounds(21, 21) || hit()){
			mAlive = false;
			return;
		}
		
		move();

		if (!eat())
			bringLastPartFirst();

		if(mTurnNextPartToCorner) {
			mTurnNextPartToCorner = false;
			mParts.front()->setCorner();
		}
	}
}

void Snake::render()
{
	auto part = mParts.begin();
	auto nextPart = ++mParts.begin();

	for(int i = 0; i < mParts.size(); i++, part++, nextPart++)
		(*part)->render(nextPart == mParts.end() ? nullptr : *nextPart);

	auto bgTexture = &sdlutils().images().at(mTextureName);

	//Cabeza viva o muerta
    SDL_Rect clipBox = build_sdlrect(2 * BOX_SIZE, mAlive ? 0 : 1 * BOX_SIZE, 1 * BOX_SIZE , 1 * BOX_SIZE);
    
    SDL_Rect textureBox = build_sdlrect(mPosition.x, mPosition.y, 1 * BOX_SIZE, 1 * BOX_SIZE);

	Vector2 orientation = mOrientation;
	if (mTurnNextPartToCorner)
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

bool Snake::eat()
{
	for(Apple& apple : mAppleGenerator->getApples())
		if(!apple.eaten && apple.posX * BOX_SIZE == mPosition.x && apple.posY * BOX_SIZE == mPosition.y){
			eatApple(apple);
			return true;
		}

	return false;
}

void Snake::eatApple(Apple& apple)
{
	apple.eaten = true;
	
	mSpeed += mSpeedIncrement;

	mParts.push_front(new SnakePart(mId, mPosition - mOrientation, mOrientation, mTextureName));
}

void Snake::move()
{
	mPosition = mNextPosition;
	mOrientation = mNextOrientation;
	mNextPosition = mPosition + mOrientation;
}

void Snake::turn(Vector2 newOrientation)
{
	mNextOrientation = newOrientation;
	mNextPosition = mPosition + mNextOrientation;
	mTurnNextPartToCorner = true;
}

void Snake::bringLastPartFirst()
{
	auto tail = mParts.back();
	mParts.pop_back();
	tail->setPositionAndOrientation(mPosition - mOrientation, mOrientation);
	mParts.push_front(tail);
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

bool Snake::outOfBounds(int rightEdge, int bottomEdge)
{
	return mNextPosition.x < 0 || mNextPosition.x >= rightEdge * BOX_SIZE
		|| mNextPosition.y < 0 || mNextPosition.y >= bottomEdge * BOX_SIZE;
}

bool Snake::hit()
{
	for (int i = 0; i < MAX_PLAYERS; i++){
		auto otherSnake = mEntity->getScene()->findEntity("Snake" + to_string(i));
		if(otherSnake.get() != nullptr){
			auto snakeComponent = otherSnake.get()->getComponent<Snake>("snake");

			if (i != mId && snakeComponent->mPosition + (snakeComponent->mAlive ? 
				snakeComponent->mNextOrientation : Vector2(0, 0)) == mNextPosition)
				return true;

			auto parts = snakeComponent->mParts;
			for (SnakePart* part : parts)
				if (part->getPosition() + (snakeComponent->mAlive ? part->getOrientation() : Vector2(0, 0)) == mNextPosition)
					return true;
		}
	}

	return false;
}

list<SnakePart*> Snake::getParts()
{
	list<SnakePart*> mParts; //No se usa
}