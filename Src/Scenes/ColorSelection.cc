#include "ColorSelection.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Image.h"
#include "../EntityComponent/Components/Text.h"
#include "../EntityComponent/Components/HostGameButton.h"

#include "../Utils/Texture.h"
#include "../Utils/SDLUtils.h"

#include "../Render/Window.h"

#include <iostream>

ColorSelection::ColorSelection() : Scene("ColorSelection")
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
        COLORS BUTTONS
    */

    auto redButton = addEntity("RedColorButton");
    redButton.get()->setDepth(3);
    auto redColorButton = new HostGameButton(&sdlutils().images().at("redButton"), 203, 523, 90, 65);	
	redButton.get()->addComponent(redColorButton);

    auto blueButton = addEntity("BlueColorButton");
    blueButton.get()->setDepth(3);
    auto blueColorButton = new HostGameButton(&sdlutils().images().at("blueButton"), 203, 592, 90, 65);	
	blueButton.get()->addComponent(blueColorButton);

    auto purpleButton = addEntity("PurpleColorButton");
    purpleButton.get()->setDepth(3);
    auto purpleColorButton = new HostGameButton(&sdlutils().images().at("purpleButton"), 300, 523, 90, 65);	
	purpleButton.get()->addComponent(purpleColorButton);

    auto yellowButton = addEntity("YellowColorButton");
    yellowButton.get()->setDepth(3);
    auto yellowColorButton = new HostGameButton(&sdlutils().images().at("yellowButton"), 300, 592, 90, 65);	
	yellowButton.get()->addComponent(yellowColorButton);


    auto grayButton = addEntity("GrayColorButton");
    grayButton.get()->setDepth(3);
    auto grayColorButton = new HostGameButton(&sdlutils().images().at("grayButton"), 405, 553, 90, 65);	
	grayButton.get()->addComponent(grayColorButton);



    /*
        COLORS DECO
    */
    auto redButtonDeco = addEntity("RedButtonDeco");
    redButtonDeco.get()->setDepth(3);
	redButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("redColorDeco"), 180, 120, 
    115 + window().getWindowWidth(), 140));

    auto blueButtonDeco = addEntity("BlueButtonDeco");
    blueButtonDeco.get()->setDepth(3);
	blueButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("blueColorDeco"), 180, 120, 
    385 + window().getWindowWidth(), 140));

    auto yellowButtonDeco = addEntity("YellowButtonDeco");
    yellowButtonDeco.get()->setDepth(3);
	yellowButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("yellowColorDeco"), 180, 120, 
    115 + window().getWindowWidth(), 283));

    auto purpleButtonDeco = addEntity("PurlpleButtonDeco");
    purpleButtonDeco.get()->setDepth(3);
	purpleButtonDeco.get()->addComponent(new Image(&sdlutils().images().at("purpleColorDeco"), 180, 120, 
    385 + window().getWindowWidth(), 283));

    /*
        
    */

}

ColorSelection::~ColorSelection(){
}