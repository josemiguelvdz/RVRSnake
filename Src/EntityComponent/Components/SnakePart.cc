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
}

SnakePart::~SnakePart()
{
	// renderManager().destroyMesh(mName);
    // TODO: ESTO ESTA BIEN?
    // SDL_free(mSnakePartsTexture);
}

void SnakePart::update(const double& dt, float speed)
{
    mPosition = mPosition + mOrientation * (float) (speed * dt);
}

void SnakePart::render(SnakePart* next)
{
    auto bgTexture = &sdlutils().images().at("snakeTexture");

    SDL_Rect clipBox;

    if (next == nullptr)
        clipBox = mTextureClips[SNAKEPARTTYPE_TAIL];

    //Si esta justo detras
    else if (next->mPosition.distance(mPosition - mOrientation) < 10)
        clipBox = mTextureClips[SNAKEPARTTYPE_BODY];
    else
        clipBox = mTextureClips[SNAKEPARTTYPE_CORNER];
    
    SDL_Rect textureBox = {mPosition.x, mPosition.y, 1 * BOX_SIZE, 1 * BOX_SIZE };


    float rotationAngle = 0;    //Derecha
    if (mOrientation.x < -.1f)
        rotationAngle = 180;    //Izquierda
    else if (mOrientation.y > .1f)
        rotationAngle= 270;     //Arriba
    else if (mOrientation.y < -.1f)
        rotationAngle = 90;     //Abajo

 	bgTexture->render(clipBox, textureBox, rotationAngle, nullptr);
}