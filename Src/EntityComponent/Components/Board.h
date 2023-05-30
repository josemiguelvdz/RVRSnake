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
	std::string mName;
	vector<vector<int>> boxes;

	int boxWidth = 32;
	int boxHeight = 32;
public:
	Board();
	~Board();
	void start() override;
	void update(const double& dt) override;
	void render() override;
};
#endif