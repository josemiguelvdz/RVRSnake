#pragma once

#ifndef __ENTITYCOMPONENT_TEXT
#define __ENTITYCOMPONENT_TEXT

#include "Component.h"
#include <string>
#include <vector>

using namespace std;

class Text : public Component
{
private:
protected:
	string mName;
    string mText;

	float mPosX;
	float mPosY;

    int mTextSize;
public:
	Text();
    Text(string text, float posX, float posY);
	~Text();
	void start() override;
	void update(const double& dt) override;
	void render() override;
};
#endif