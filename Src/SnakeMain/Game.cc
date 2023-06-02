#include "Game.h"

#include <thread>

#include "../Input/InputManager.h"
#include "../Input/InputCode.h"

#include "../Render/Window.h"

#include "../Scenes/SceneManager.h"
#include "../Scenes/Battle.h"
#include "../Scenes/TitleScreen.h"
#include "../Scenes/OnlineSelection.h"

#include "../Network/NetworkManager.h"

#include "../Utils/Time.h"
#include "../Utils/SDLUtils.h"

#include <SDL2/SDL.h>

bool Game::setup(std::string gameName)
{
    Window::Init(SDL_INIT_EVERYTHING, gameName.c_str(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 672, 672, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Load Resources
	sdlutils().initSDLExtensions();
	sdlutils().loadResources();

    // Init Input
	createInput();

	// Load Scene
	// Scene* battleTest = new Battle(1);
	// sceneManager().loadScene(battleTest);
	// Scene* titleScreen = new TitleScreen();
	// sceneManager().loadScene(titleScreen);

	Scene* multiScren = new OnlineSelection();
	sceneManager().change(multiScren);
	
	// Start time
	mTime = new Time(60);

	// mPlayerName = "Snake";

	return true;
}

void Game::loop()
{
	SDL_Event event;
	bool quit = false;
	inputManager().addEvent(QuitLoop, &quit);
	float dt;

	while (!quit && !sceneManager().isQuiting()) {
		while (SDL_PollEvent(&event)) { }

		// Update Time Values
		dt = mTime->update();
		
		// Update the scene
		// physicsManager().update(dt, 0, 1 / mTime->getTargetFrameRate());

		// soundManager().systemRefresh(dt);

		sdlutils().clearRenderer();

		// Update the scene
		sceneManager().update(dt);

		// Render the scene
		sceneManager().render();
		
		sdlutils().presentRenderer();
		
		//If we're going to change the scene
		if (sceneManager().isChanging())
			sceneManager().loadScene(sceneManager().getNewScene());

		// Wait time
		std::this_thread::sleep_for(std::chrono::milliseconds(mTime->millisecondsToNextFrame()));
	}
}

void Game::exit()
{
	// Clear the memory created in the execution of the program
	NetworkManager::Shutdown();
	SceneManager::Shutdown();
	// PhysicsManager::Shutdown();
	// RenderManager::Shutdown();
	Window::Shutdown();
	// SoundManager::Shutdown();
	// ComponentsFactory::Shutdown();
	InputManager::Shutdown();

	delete mTime;
}

int Game::QuitLoop(void* userdata, SDL_Event* event)
{
	if (event->type == SDL_QUIT) {
		bool* quit = (bool*)userdata;
		*quit = true;
	}

	return 0;
}

void Game::createInput()
{
	/*
		KEYBOARD
	*/
	AxisInput wasdHorizontal, arrowHorizontal;
	wasdHorizontal.type = INPUTTYPE_KEYBOARD;
	wasdHorizontal.positive = KEYBOARDCODE_D;
	wasdHorizontal.negative = KEYBOARDCODE_A;

	arrowHorizontal.type = INPUTTYPE_KEYBOARD;
	arrowHorizontal.positive = KEYBOARDCODE_RIGHT; 
	arrowHorizontal.negative = KEYBOARDCODE_LEFT;

	AxisInfo horizontalInfo;
	horizontalInfo.dead = .1f;
	horizontalInfo.gravity = .4f;

	inputManager().addAxis("horizontal", horizontalInfo, wasdHorizontal);
	inputManager().addBinding("horizontal", arrowHorizontal);

	AxisInput wasdVertical, arrowVertical;
	wasdVertical.type = INPUTTYPE_KEYBOARD;
	wasdVertical.positive = KEYBOARDCODE_W;
	wasdVertical.negative = KEYBOARDCODE_S;

	arrowVertical.type = INPUTTYPE_KEYBOARD;
	arrowVertical.positive = KEYBOARDCODE_UP; 
	arrowVertical.negative = KEYBOARDCODE_DOWN;

	AxisInfo verticalInfo;
	verticalInfo.dead = .1f;
	verticalInfo.gravity = .4f;

	inputManager().addAxis("vertical", verticalInfo, wasdVertical);
	inputManager().addBinding("vertical", arrowVertical);


	/*
		MOUSE
	*/
	Input mouseClick;
	mouseClick.type = INPUTTYPE_MOUSE_CLICK;
	mouseClick.which = MOUSE_LEFTCLICK;
	inputManager().addButton("leftclick", mouseClick);
}

std::string Game::getPlayerName() {
	return mPlayerName;
}

Game::Game() {
}

Game::~Game()
{
}