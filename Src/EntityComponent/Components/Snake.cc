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

Snake::Snake(int id, Vector2 position, Vector2 orientation) : mId(id), 
	mPosition(position * BOX_SIZE), mOrientation(orientation * BOX_SIZE)
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

	mTextureName = gameManager()->playerColorTextureNames[gameManager()->playerColors[mId]];

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
	if(!networkManager().initialized() || networkManager().getClientId() == mId){
		//No se puede ir en tu direccion actual ni en la opuesta
		//Solo se permiten giros de 90 grados
		if (abs(mOrientation.x) < .1f && inputManager().getAxis("horizontal") > .1f)
			turn({ BOX_SIZE, 0 }, networkManager().initialized() && !networkManager().isHost()); 	//Derecha
		else if (abs(mOrientation.x) < .1f && inputManager().getAxis("horizontal") < -.1f)
			turn({ -BOX_SIZE, 0 }, networkManager().initialized() && !networkManager().isHost()); 	//Izquierda
		else if (abs(mOrientation.y) < .1f && inputManager().getAxis("vertical") > .1f)
			turn({ 0, -BOX_SIZE }, networkManager().initialized() && !networkManager().isHost()); 	//Arriba
		else if (abs(mOrientation.y) < .1f && inputManager().getAxis("vertical") < -.1f)
			turn({ 0, BOX_SIZE }, networkManager().initialized() && !networkManager().isHost()); 	//Abajo
	}

	//Solo el host mueve las serpientes
	if ((!networkManager().initialized() || networkManager().isHost()) && mTimer->getRawSeconds() >= 1 / mSpeed) {
		mTimer->reset();

		bool ate = false;
		bool turnNextPartToCorner;

		if (outOfBounds(21, 21) || hit())
			mAlive = false;
		else{
			move();

			ate = eat();
			if (ate)
				mParts.push_front(new SnakePart(mId, mPosition - mOrientation, mOrientation, mTextureName));
			else
				bringLastPartFirst();

			turnNextPartToCorner = mTurnNextPartToCorner;

			if (mTurnNextPartToCorner) {
				mTurnNextPartToCorner = false;
				mParts.front()->setCorner();
			}
		}

		if (networkManager().initialized())
			networkManager().syncSnake(mId, mPosition, mOrientation, mAlive, ate, turnNextPartToCorner);
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
    else if (orientation.y < -.1f) 	//Arriba
        rotationAngle = 270;

 	bgTexture->render(clipBox, textureBox, rotationAngle, nullptr);
}

bool Snake::eat()
{
	for(Apple& apple : mAppleGenerator->getApples())
		if(!apple.eaten && apple.posX * BOX_SIZE == mPosition.x && apple.posY * BOX_SIZE == mPosition.y){
			eatApple(apple, networkManager().initialized());
			return true;
		}

	return false;
}

void Snake::eatApple(Apple& apple, bool sendMessage)
{
	apple.eaten = true;
	
	mSpeed += mSpeedIncrement;

	if (sendMessage)
		networkManager().syncApple(mId, Vector2(apple.posX, apple.posY), true);
}

void Snake::move()
{
	mPosition = mNextPosition;
	mOrientation = mNextOrientation;
	mNextPosition = mPosition + mOrientation;
}

void Snake::turn(Vector2 newOrientation, bool sendMessage)
{
	mNextOrientation = newOrientation;
	mNextPosition = mPosition + mNextOrientation;
	mTurnNextPartToCorner = mNextOrientation.distance(mParts.front()->getOrientation()) > 1;

	if (sendMessage)
		networkManager().syncSnake(mId, mPosition, newOrientation, mAlive, false, mTurnNextPartToCorner);
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

			//Choque con otras cabezas
			if (i != mId && snakeComponent->mPosition + (snakeComponent->mAlive ? 
				snakeComponent->mNextOrientation : Vector2(0, 0)) == mNextPosition)
				return true;

			//Choque con todas las partes de cuerpo de la serpiente
			auto parts = snakeComponent->mParts;
			for (SnakePart* part : parts)
				if (part->getPosition() + (snakeComponent->mAlive ? part->getOrientation() : Vector2(0, 0)) == mNextPosition)
					return true;
		}
	}

	return false;
}

void Snake::syncSnake(Vector2 position, Vector2 orientation, bool alive, bool ate, bool turnNextPartToCorner) {
	mAlive = alive;

	if(!mAlive)
		return;

	mPosition = position;
	mOrientation = orientation;
	mNextPosition = mPosition + mOrientation;

	if (ate)
		mParts.push_front(new SnakePart(mId, mPosition - mOrientation, mOrientation, mTextureName));
	else
		bringLastPartFirst();

	if (turnNextPartToCorner) 
		mParts.front()->setCorner();
};