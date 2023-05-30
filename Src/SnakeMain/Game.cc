#include "Game.h"

#include <thread>

#include "../Input/InputManager.h"
#include "../Scenes/SceneManager.h"
#include "../Render/Window.h"

// #include "EntityComponent/Scene.h"
// #include "EntityComponent/Components/ComponentsFactory.h"
// #include "EntityComponent/Components/FactoryComponent.h"

#include "../Scenes/Battle.h"

#include "../Utils/SDLUtils.h"

#include "../Utils/Time.h"
// #include "Utils/Timer.h"

#include <SDL2/SDL.h>

bool Game::setup(std::string gameName)
{
    Window::Init(SDL_INIT_EVERYTHING, gameName.c_str(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 672, 672, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Load Resources
	sdlutils().initSDLExtensions();
	sdlutils().loadResources();

    // Init Input
	// TODO: Create Inputs of the Snake

	// Start time
	mTime = new Time(60);

	// Load Scene
	Scene* battleTest = new Battle(1);
	sceneManager().loadScene(battleTest);
	
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
	SceneManager::Shutdown();
	// PhysicsManager::Shutdown();
	// RenderManager::Shutdown();
	Window::Shutdown();
	// SoundManager::Shutdown();
	// ComponentsFactory::Shutdown();
	InputManager::Shutdown();

	delete mTime;
}


// void me::MotorEngine::initFactories()
// {
// 	componentsFactory().addFactoryComponent("transform", new FactoryTransform());
// 	componentsFactory().addFactoryComponent("uitransform", new FactoryUITransform());
// 	componentsFactory().addFactoryComponent("rigidbody", new FactoryRigidBody());
// 	componentsFactory().addFactoryComponent("animator", new FactoryAnimator());
// 	componentsFactory().addFactoryComponent("meshrenderer", new FactoryMeshRenderer());
// 	componentsFactory().addFactoryComponent("uispriterenderer", new FactoryUISpriteRenderer());
// 	componentsFactory().addFactoryComponent("collider", new FactoryCollider());
// 	componentsFactory().addFactoryComponent("camera", new FactoryCamera());
// 	componentsFactory().addFactoryComponent("audiosource", new FactoryAudioSource());
// 	componentsFactory().addFactoryComponent("audiolistener", new FactoryAudioListener());
// 	componentsFactory().addFactoryComponent("light", new FactoryLight());
// 	componentsFactory().addFactoryComponent("uitext", new FactoryUIText());
// }

int Game::QuitLoop(void* userdata, SDL_Event* event)
{
	if (event->type == SDL_QUIT) {
		bool* quit = (bool*)userdata;
		*quit = true;
	}

	return 0;
}

Game::Game() {
}

Game::~Game()
{
}