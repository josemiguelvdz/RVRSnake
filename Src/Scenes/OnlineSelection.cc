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
	ipTextBox.get()->addComponent(new Image("textBox", 280, 100, 355, 285));


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

    // //Boton para escribir el nombre
	// nombre = new UiButton(mGame, mGame->getNombre(), "ip", { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, sdlutils().width() / 2 - 120, opcPant->getHeight() - 200);
	// cursor_ = new GameObject(mGame);
	// nombre->setInitialPosition(sdlutils().width() / 2 - 120, opcPant->getHeight() - 200);
	// nombre->setActive(false);
	
	// nombre->setAction([this](Game* mGame, bool& exit) {

	// 	char c = ih().getTypedKey();
	// 	string nombrePlayer = mGame->getNombre();

	// 	if (c != ' ')
	// 	{
	// 		if (c == '\b')
	// 		{

	// 			if (!nombrePlayer.empty())
	// 				nombrePlayer.pop_back();
	// 			else
	// 				nombrePlayer = ' ';
	// 		}

	// 		else if (nombrePlayer.size() < maxCaracteres) {
	// 			nombrePlayer += c;
	// 		}

	// 		if (nombrePlayer.empty())
	// 			nombrePlayer = ' ';

	// 		mGame->setNombre(nombrePlayer);

	// 		nombre->setTexture(nombrePlayer, string("ip"), { 255, 255, 255, 255 }, { 0, 0, 0, 0 });
	// 		nombre->setDimension();
	// 	}
	// 	nombre->render(nullptr);
	// 	});

	// optionsMenu.push_back(nombre);

    /*
        BACK BUTTON
    */
}

OnlineSelection::~OnlineSelection(){
}