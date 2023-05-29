#include "Board.h"
#include "../../Render/Window.h"
#include "../Entity.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Board::Board()
{
    groundTexture = nullptr;
}


Board::~Board()
{
	// renderManager().destroyMesh(mName);
    // TODO: ESTO ESTA BIEN?
    SDL_free(groundTexture);
}

void Board::init()
{
	// Load textures
    // SDL_Texture* ballTexture = IMG_LoadTexture(window().getRenderer(), "../../../Resources/gfx/tile32_light.png");
}

void Board::start()
{
	// mTransform = getEntity()->getComponent<Transform>("transform");

	// assert(mTransform && "An Entity doesn't have the transform component");

	// renderManager().setMeshTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
    int nBoxes = window().getWindowWidth() / boxWidth;
    
    for(int i = 0; i < nBoxes; i++){
        for (int j = 0; j < nBoxes; j++){
            // Put image in coords i * boxWidth, j * boxHeight
            boxes[i][j].playerID = -1;
            
        }
    }
}

void Board::update(const double& dt)
{
	// if (!mStaticObject)
	// 	renderManager().setMeshTransform(mName, mTransform->getPosition(), mTransform->getScale(), mTransform->getRotation());
}

std::string Board::getName()
{
	return mName;
}

void Board::setName(std::string name)
{
	mName = name;
}
