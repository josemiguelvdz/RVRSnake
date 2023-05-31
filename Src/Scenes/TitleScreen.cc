#include "TitleScreen.h"
#include "../EntityComponent/Entity.h"

#include "../EntityComponent/Components/Image.h"
#include "../EntityComponent/Components/Text.h"

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

	
	auto splashBg = new Image("authorsBg", 800, 480, 0, 200);
	authorBg.get()->addComponent(splashBg);

	// Text
	auto author1Text = addEntity("author1Text");
	author1Text.get()->setDepth(2);
	author1Text.get()->addComponent(new Text("Jose Miguel Villacanas", window().getWindowWidth() / 2 - 180, window().getWindowHeight() / 2 - 48));

	auto author2Text = addEntity("author2Text");
	author2Text.get()->setDepth(2);
	author2Text.get()->addComponent(new Text("Javier Cano", window().getWindowWidth() / 2 - 90, window().getWindowHeight() / 2));

	/*
		TITLE IMAGE
	*/
	// auto title = addEntity("Title");
	// title.get()->setDepth(1);

	// auto image = new Image("gameLogo", 350, 230, window().getWindowWidth() / 2 - (350.0f / 2.0f) , window().getWindowHeight() / 6);
	// image->playSimpleSweepAnim();
	// title.get()->addComponent(image);
	

	// title.get()->addComponent()
}

TitleScreen::~TitleScreen(){
}