#include "Board.h"
#include "../../Render/Window.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"

Board::Board() : mName("board")
{
    int nBoxes = window().getWindowWidth() / boxWidth;
    boxes = std::vector<std::vector<int>>(nBoxes, std::vector<int>(nBoxes, -1));
}


Board::~Board()
{
}

void Board::start()
{

}


void Board::update(const double& dt)
{
	int nBoxes = window().getWindowWidth() / boxWidth;

    groundTexture = &sdlutils().images().at("tileLight32");
    
    for(int i = 0; i < boxes.size(); i++){
        for (int j = 0; j < boxes[0].size(); j++){
            // Put image in coords i * boxWidth, j * boxHeight
            SDL_Rect textureBox;

            textureBox = {i * boxWidth, j * boxHeight, boxWidth, boxHeight };

		    groundTexture->render(textureBox);
	    }
    }
}
