#pragma once

#ifndef __ENTITYCOMPONENT_BOARD
#define __ENTITYCOMPONENT_BOARD

#include "Component.h"
#include <string>
#include <vector>

using namespace std;

class Texture;

// struct Box {
// 	int playerID;
// };

class Board : public Component
{
private:
protected:
	int boxWidth = 32;
	int boxHeight = 32;
public:
	Board();
	~Board();

	void render() override;
};
#endif