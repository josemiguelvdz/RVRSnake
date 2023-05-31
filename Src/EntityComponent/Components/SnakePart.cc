#include "SnakePart.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"

#include <iostream>
#include <list>
#include <math.h>

using namespace std;

SnakePart::SnakePart(int id, Vector2 position, Vector2 orientation) : mId(id), mPosition(position), mOrientation(orientation)
{
    mTextureClips[SNAKEPARTTYPE_BODY] = build_sdlrect(1 * BOX_SIZE, 0, 1 * BOX_SIZE, 1 * BOX_SIZE);
    mTextureClips[SNAKEPARTTYPE_HEAD] = build_sdlrect(2 * BOX_SIZE, 0, 1 * BOX_SIZE, 1 * BOX_SIZE);
    mTextureClips[SNAKEPARTTYPE_TAIL] = build_sdlrect(0, 1 * BOX_SIZE, 1 * BOX_SIZE, 1 * BOX_SIZE);
    mTextureClips[SNAKEPARTTYPE_CORNER] = build_sdlrect(0, 0, 1 * BOX_SIZE, 1 * BOX_SIZE);

    isCorner = false;
}

SnakePart::~SnakePart()
{
	// renderManager().destroyMesh(mName);
    // TODO: ESTO ESTA BIEN?
    // SDL_free(mSnakePartsTexture);
}

void SnakePart::update(const double& dt, float speed)
{
    //mPosition = mPosition + mOrientation * (float) (speed * dt);
}

void SnakePart::render(SnakePart* next)
{
    auto bgTexture = &sdlutils().images().at("snakeTexture");

    SDL_Rect clipBox;

    float rotationOffset = 0;

    if (next == nullptr)
        clipBox = mTextureClips[SNAKEPARTTYPE_TAIL];

    else if (!isCorner)
        clipBox = mTextureClips[SNAKEPARTTYPE_BODY];
    else {
        clipBox = mTextureClips[SNAKEPARTTYPE_CORNER];

        if (mOrientation.x > .1f && next->mOrientation.y > .1f //Derecha
            || mOrientation.x < -.1f && next->mOrientation.y < -.1f //Izquierda
            || mOrientation.y > .1f && next->mOrientation.x < -.1f //Abajo
            || mOrientation.y < -.1f && next->mOrientation.x > .1f) //Arriba
            rotationOffset = -90;
    }
    
    SDL_Rect textureBox = {mPosition.x, mPosition.y, 1 * BOX_SIZE, 1 * BOX_SIZE };


    float rotationAngle = 0;    //Derecha
    if (mOrientation.x < -.1f)
        rotationAngle = 180;    //Izquierda
    else if (mOrientation.y > .1f)
        rotationAngle = 90;     //Abajo
    else if (mOrientation.y < -.1f)
        rotationAngle = 270;     //Arriba

 	bgTexture->render(clipBox, textureBox, rotationAngle + rotationOffset, nullptr);
}

void SnakePart::setPositionAndOrientation(Vector2 position, Vector2 orientation) 
{
    mPosition = position;
    mOrientation = orientation;
    snap();
    isCorner = false;
}

Vector2 SnakePart::getPosition() 
{
    return mPosition;
}

Vector2 SnakePart::getOrientation() 
{
    return mOrientation;
}

void SnakePart::setCorner() 
{
    isCorner = true;
}

void SnakePart::snap() {
	snapX();
	snapY();
}

void SnakePart::snapX()
{
    int xPosition = mPosition.x / BOX_SIZE;
	float xOffset = mPosition.x / BOX_SIZE - xPosition;

	if(xOffset < .5f)
		mPosition.x = xPosition * BOX_SIZE;
	else
		mPosition.x = (xPosition + 1) * BOX_SIZE;
}

void SnakePart::snapY()
{
    int yPosition = mPosition.y / BOX_SIZE;
	float yOffset = mPosition.y / BOX_SIZE - yPosition;

	if(yOffset < .5f)
		mPosition.y = yPosition * BOX_SIZE;
	else
		mPosition.y = (yPosition + 1) * BOX_SIZE;
}