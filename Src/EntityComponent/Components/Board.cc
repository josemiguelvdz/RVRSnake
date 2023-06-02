#include "Board.h"
#include "../../Render/Window.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"

Board::Board()
{
    mName = "board";
}


Board::~Board()
{
}

void Board::render(){
    /*
        RENDERIZAR FONDO TABLERO
    */
    auto bgTexture = &sdlutils().images().at("battleBackground");
    SDL_Rect textureBox = {0, 0, window().getWindowWidth(), window().getWindowHeight() };
 	bgTexture->render(textureBox);

    /*
        VER CASILLAS
    */
    // int nBoxes = window().getWindowWidth() / boxWidth;

    // auto groundTexture = &sdlutils().images().at("tileLight32");
    
    // for(int i = 0; i < boxes.size(); i++){
    //     for (int j = 0; j < boxes[0].size(); j++){
    //         // Put image in coords i * boxWidth, j * boxHeight
    //         SDL_Rect textureBox;

    //         textureBox = {i * boxWidth, j * boxHeight, boxWidth, boxHeight };

	// 	    groundTexture->render(textureBox);
	//     }
    // }
}