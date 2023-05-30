#include "TitleScreen.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Image.h"
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
		TITLE IMAGE
	*/
	auto title = addEntity("Title");
	title.get()->setDepth(1);
	title.get()->addComponent(new Image("gameLogo", 319, 201, window().getWindowWidth() / 2 , window().getWindowHeight() / 2));
}

TitleScreen::~TitleScreen(){
}