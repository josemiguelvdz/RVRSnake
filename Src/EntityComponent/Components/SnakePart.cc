#include "SnakePart.h"
#include "../Entity.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;


SnakePart::SnakePart(int id)
{
    // mSnakePartsTexture = nullptr;
}

SnakePart::~SnakePart()
{
	// renderManager().destroyMesh(mName);
    // TODO: ESTO ESTA BIEN?
    // SDL_free(mSnakePartsTexture);
}