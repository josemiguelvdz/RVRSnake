#include "TitleScreen.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Image.h"
#include "../EntityComponent/Components/Text.h"
#include "../EntityComponent/Components/SinglePlayerButton.h"
#include "../EntityComponent/Components/MultiPlayerButton.h"
#include "../EntityComponent/Components/GameManager.h"

#include "../Utils/Texture.h"
#include "../Utils/SDLUtils.h"

#include "../Render/Window.h"

#include <iostream>

TitleScreen::TitleScreen() : Scene("TitleScreen")
{
	/*
		BACKGROUND
	*/
	auto background = addEntity("Background");
	background.get()->addComponent(new Image("battleBackground", 672, 672, 0, 0));


	/*
		AUTHORS
	*/
	auto authorBg = addEntity("authorBg");
	authorBg.get()->setDepth(1);

	
	auto splashBg = new Image("authorsBg", 672, 672, 0, 0);
	authorBg.get()->addComponent(splashBg);
	SDL_SetTextureAlphaMod(splashBg->getTexture()->getSdlTexture(), 0);
	splashBg->getTexture()->startToAppear();
	splashBg->getTexture()->startToDissappear(6.0f);


	// Text
	auto author1Text = addEntity("author1Text");
	author1Text.get()->setDepth(2);
	auto author1Texture = new Text("Jose Miguel Villacanas", window().getWindowWidth() / 2 - 200, window().getWindowHeight() / 2 - 48);
	author1Text.get()->addComponent(author1Texture);

	SDL_Color color = {255, 255, 255, 255};
	author1Texture->setTexture(new Texture(window().getRenderer(), "Jose Miguel Villacanas", sdlutils().fonts().at("gameFont"), color));

	SDL_SetTextureAlphaMod(author1Texture->getTexture()->getSdlTexture(), 0);
	author1Texture->getTexture()->startToAppear();
	author1Texture->getTexture()->startToDissappear(8.0f);

	auto author2Text = addEntity("author2Text");
	author2Text.get()->setDepth(2);
	auto author2Texture = new Text("Javier Cano", window().getWindowWidth() / 2 - 105, window().getWindowHeight() / 2);
	author2Text.get()->addComponent(author2Texture);

	author2Texture->setTexture(new Texture(window().getRenderer(), "Javier Cano", sdlutils().fonts().at("gameFont"), color));

	SDL_SetTextureAlphaMod(author2Texture->getTexture()->getSdlTexture(), 0);
	author2Texture->getTexture()->startToAppear();
	author2Texture->getTexture()->startToDissappear(8.0f);


	/*
		TITLE IMAGE
	*/
	auto title = addEntity("Title");
	title.get()->setDepth(1);

	auto image = new Image("gameLogo", 350, 230, window().getWindowWidth() / 2 - (350.0f / 2.0f) , window().getWindowHeight() / 6);
	title.get()->addComponent(image);

	image->playSimpleSweepAnim();
	SDL_SetTextureAlphaMod(image->getTexture()->getSdlTexture(), 0);

	image->getTexture()->startToAppear(12.0f);

	/*
		BUTTONS
	*/
	auto singleplayer = addEntity("SinglePlayerButton");
	singleplayer.get()->setDepth(1);

	auto singleplayerButton = new SinglePlayerButton(&sdlutils().images().at("singleplayerButton"), window().getWindowWidth() / 2 - (350.0f / 2.0f), 
	window().getWindowHeight() - 270, 350, 100);
	SDL_SetTextureAlphaMod(singleplayerButton->getTexture()->getSdlTexture(), 0);
	singleplayerButton->getTexture()->startToAppear(12.0f);
	
	singleplayer.get()->addComponent(singleplayerButton);

	
	auto multiplayer = addEntity("MultiPlayerButton");
	multiplayer.get()->setDepth(1);

	auto multiplayerButton = new MultiPlayerButton(&sdlutils().images().at("multiplayerButton"), window().getWindowWidth() / 2 - (350.0f / 2.0f), 
	window().getWindowHeight() - 150, 350, 100);
	SDL_SetTextureAlphaMod(multiplayerButton->getTexture()->getSdlTexture(), 0);
	multiplayerButton->getTexture()->startToAppear(12.0f);
	
	multiplayer.get()->addComponent(multiplayerButton);	

	/*
		GAME MANAGER
	*/

	// auto gameManager = addEntity("GameManager");
	// gameManager.get()->addComponent(new GameManager());
}

TitleScreen::~TitleScreen(){
}