#include "ColorSelection.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Image.h"
#include "../EntityComponent/Components/Text.h"
#include "../EntityComponent/Components/HostGameButton.h"
#include "../EntityComponent/Components/GameManager.h"

#include "../Utils/Texture.h"
#include "../Utils/SDLUtils.h"

#include "../Render/Window.h"

#include <iostream>

ColorSelection::ColorSelection(std::vector<std::string> names, std::vector<int> colors, bool isHost) : Scene("ColorSelection")
{
	/*
		BACKGROUND
	*/
	auto background = addEntity("Background");
	background.get()->addComponent(new Image("battleBackground", 672, 672, 0, 0));

    auto menuLayer = addEntity("MenuLayer");
    menuLayer.get()->addComponent(new Image("networkMenuBg", 672, 672, 0, 0));
    menuLayer.get()->setDepth(1);

    /*
        NETWORK DECORATION
    */
    auto colorSelectionDeco = addEntity("ColorSelectionDeco");
    colorSelectionDeco.get()->addComponent(new Image("colorSelectionDeco", 672, 672, 0, 0));
    colorSelectionDeco.get()->setDepth(2);

    /*
        PLAY BUTTON
    */
    if (isHost){
        
    }

    /*
        COLORS DECO
    */
    

    for (int i = 0; i < 4; i++){
        if (gameManager()->playerNames[i] != " "){
            SnakeColor myColor = gameManager()->playerColors[i];

            switch(i){
                case 0:
                {
                    // Red always
                    auto redButtonDeco = addEntity("RedButtonDeco");
                    redButtonDeco.get()->setDepth(3);
                    redButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("redColorDeco"), 180, 120, 
                    107, 140));
                }
                break;
                case 1:
                {
                    if (myColor == SNAKECOLOR_BLUE){
                        auto blueButtonDeco = addEntity("BlueButtonDeco");
                        blueButtonDeco.get()->setDepth(3);
                        blueButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("blueColorDeco"), 180, 120, 
                        385, 140));
                    }
                    else if (myColor == SNAKECOLOR_YELLOW){
                        auto yellowButtonDeco = addEntity("YellowButtonDeco");
                        yellowButtonDeco.get()->setDepth(3);
                        yellowButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("yellowColorDeco"), 180, 120, 
                        385, 140));
                    }
                    else if (myColor == SNAKECOLOR_PURPLE){
                        auto purpleButtonDeco = addEntity("PurpleButtonDeco");
                        purpleButtonDeco.get()->setDepth(3);
                        purpleButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("purpleColorDeco"), 180, 120, 
                        385, 140));
                    }
                }
                break;
                case 2:
                {
                    if (myColor == SNAKECOLOR_BLUE){
                        auto blueButtonDeco = addEntity("BlueButtonDeco");
                        blueButtonDeco.get()->setDepth(3);
                        blueButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("blueColorDeco"), 180, 120, 
                        107, 283));
                    }
                    else if (myColor == SNAKECOLOR_YELLOW){
                        auto yellowButtonDeco = addEntity("YellowButtonDeco");
                        yellowButtonDeco.get()->setDepth(3);
                        yellowButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("yellowColorDeco"), 180, 120, 
                        107, 283));
                    }
                    else if (myColor == SNAKECOLOR_PURPLE){
                        auto purpleButtonDeco = addEntity("PurpleButtonDeco");
                        purpleButtonDeco.get()->setDepth(3);
                        purpleButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("purpleColorDeco"), 180, 120, 
                        107, 283));
                    }
                }
                break;
                case 3:
                {
                        if (myColor == SNAKECOLOR_BLUE){
                        auto blueButtonDeco = addEntity("BlueButtonDeco");
                        blueButtonDeco.get()->setDepth(3);
                        blueButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("blueColorDeco"), 180, 120, 
                        385, 283));
                    }
                    else if (myColor == SNAKECOLOR_YELLOW){
                        auto yellowButtonDeco = addEntity("YellowButtonDeco");
                        yellowButtonDeco.get()->setDepth(3);
                        yellowButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("yellowColorDeco"), 180, 120, 
                        385, 283));
                    }
                    else if (myColor == SNAKECOLOR_PURPLE){
                        auto purpleButtonDeco = addEntity("PurpleButtonDeco");
                        purpleButtonDeco.get()->setDepth(3);
                        purpleButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("purpleColorDeco"), 180, 120, 
                        385, 283));
                    }
                }
                break;
            }
        }
    }
   

    /*
        NAMES
    */
	auto player1Text = addEntity("Player1Text");
	player1Text.get()->setDepth(4);
    
    if (names[0].size() < 1)
        names[0] = " ";

	auto player1Texture = new Text(names[0], 115, 180);
	player1Text.get()->addComponent(player1Texture);

	SDL_Color color = {255, 255, 255, 255};
	player1Texture->setTexture(new Texture(window().getRenderer(), names[0], sdlutils().fonts().at("gameFont"), color));

    // ---------------------
    auto player2Text = addEntity("Player2Text");
	player2Text.get()->setDepth(4);

    if (names[1].size() < 1)
        names[1] = " ";

	auto player2Texture = new Text(names[1], 387, 180);
	player2Text.get()->addComponent(player2Texture);

	player2Texture->setTexture(new Texture(window().getRenderer(), names[1], sdlutils().fonts().at("gameFont"), color));

    // ---------------------
    auto player3Text = addEntity("Player3Text");
	player3Text.get()->setDepth(4);

    if (names[2].size() < 1)
        names[2] = " ";

	auto player3Texture = new Text(names[2], 115, 312);
	player3Text.get()->addComponent(player3Texture);

	player3Texture->setTexture(new Texture(window().getRenderer(), names[2], sdlutils().fonts().at("gameFont"), color));

    // ---------------------

    auto player4Text = addEntity("Player4Text");
	player4Text.get()->setDepth(4);

    if (names[3].size() < 1)
        names[3] = " ";

	auto player4Texture = new Text(names[3], 387, 312);
	player4Text.get()->addComponent(player4Texture);

	player4Texture->setTexture(new Texture(window().getRenderer(), names[3], sdlutils().fonts().at("gameFont"), color));
    
    // TODO: names DECO

}

ColorSelection::~ColorSelection(){
}