#include "OnlineSelection.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Image.h"
#include "../EntityComponent/Components/Text.h"
#include "../EntityComponent/Components/HostGameButton.h"

#include "../Utils/Texture.h"
#include "../Utils/SDLUtils.h"

#include "../Render/Window.h"

#include <iostream>

OnlineSelection::OnlineSelection() : Scene("OnlineSelection")
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
    auto menuDeco = addEntity("MenuDecoration");
    menuDeco.get()->addComponent(new Image("networkMenuDeco", 672, 672, 0, 0));
    menuDeco.get()->setDepth(2);

    /*
        HOST GAME BUTTON
    */
    auto hostGame = addEntity("HostGameButton");
    hostGame.get()->setDepth(3);

    auto hostGameButton = new HostGameButton(&sdlutils().images().at("hostButton"), 125, 310, 120, 90);	
	hostGame.get()->addComponent(hostGameButton);

    /*
        IP TEXT BOX
    */
    auto ipTextBox = addEntity("IpTextBox");
    ipTextBox.get()->setDepth(3);
	ipTextBox.get()->addComponent(new Image("ipTextBox", 280, 100, 355, 285));


    /*
        JOIN GAME BUTTON
    */
    auto joinGame = addEntity("JoinGameButton");
    joinGame.get()->setDepth(3);

    auto joinGameButton = new HostGameButton(&sdlutils().images().at("joinButton"), 440, 380, 120, 90);	
	joinGame.get()->addComponent(joinGameButton);


    /*
        NAME
    */

    /*
        BACK BUTTON
    */
}

OnlineSelection::~OnlineSelection(){
}