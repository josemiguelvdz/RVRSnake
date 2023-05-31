#include "SnakePart.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"

#include <iostream>
#include <list>

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
    Vector2 newPosition = mPosition + mOrientation * (float) (speed * dt);
    cout << "Pos: " << mPosition.x << " " << mPosition.y << " NewPos: " << newPosition.x << " " << newPosition.y << dt << endl;
    mPosition = newPosition;
}

void SnakePart::render(SnakePart* next, bool first)
{
    auto bgTexture = &sdlutils().images().at("snakeTexture");

    SDL_Rect clipBox;

    if(first)
        clipBox = mTextureClips[SNAKEPARTTYPE_HEAD];
    else if (next == nullptr)
        clipBox = mTextureClips[SNAKEPARTTYPE_TAIL];

    //Si esta justo detras
    else if (next->mPosition == mPosition - mOrientation)
        clipBox = mTextureClips[SNAKEPARTTYPE_BODY];
    else
        clipBox = mTextureClips[SNAKEPARTTYPE_CORNER];
    
    SDL_Rect textureBox = {mPosition.x, mPosition.y, 1 * BOX_SIZE, 1 * BOX_SIZE };

 	bgTexture->render(clipBox, textureBox);
}