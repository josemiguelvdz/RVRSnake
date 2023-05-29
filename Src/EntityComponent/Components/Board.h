#pragma once

#ifndef __ENTITYCOMPONENT_BOARD
#define __ENTITYCOMPONENT_BOARD

#include "Component.h"
#include <string>
#include <vector>

/**

*/
using namespace std;

class SDL_Texture;

struct Box {
	int playerID;
};

class Board : public Component
{
private:
protected:
	std::string mName;

	SDL_Texture* groundTexture; 
	vector<vector<Box>> boxes;

	int boxWidth = 32;
	int boxHeight = 32;
public:

	/**

	*/
	Board();
	~Board();

	void init();

	/**
	
	*/
	void start() override;
	

	/**
	
	*/
	void update(const double& dt) override;
};
#endif