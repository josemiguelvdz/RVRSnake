#pragma once
#ifndef __RVR_GAME
#define __RVR_GAME

#include <chrono>
#include <string>

union SDL_Event;
class Time;
class NetworkManager;

class Game {
public:
	Game();
	~Game();

	/**
	Loads and initializates the engine and the game.
	Automatically loads a _d sufix dll if _DEBUG flags is defined.
	@params gameName Name of the .dll of the game, without any sufixes
	*/
	bool setup(std::string gameName = "MultiSnake");
	void loop();
	void exit();

private:
	/*
	* If we press SDL_QUIT (Exit button), the game stops and closes
	* @param userData is the aditional information of the SDL callback. By default, userData contains nullptr.
	* @param event is a SDL variable that contains information about the SDL_Event launched by any event.
	* @returns is ignored
	*/
	static int QuitLoop(void* userdata, SDL_Event* event);

	void createInput();

	Time* mTime;
};

#endif