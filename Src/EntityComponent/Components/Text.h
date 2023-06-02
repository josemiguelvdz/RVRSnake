#pragma once

#ifndef __ENTITYCOMPONENT_TEXT
#define __ENTITYCOMPONENT_TEXT

#include "Component.h"
#include <string>
#include <vector>

using namespace std;

class Texture;
class SDL_Color;

class Text : public Component
{
private:
protected:
    string mText;

	float mPosX;
	float mPosY;

    int mTextSize;
	Texture* mTextTexture;
public:
	Text();
    Text(string text, float posX, float posY);
	~Text();
	void start() override;
	void update(const double& dt) override;
	void render() override;

	inline Texture* getTexture(){
		return mTextTexture;
	}

	inline void setTexture(Texture* newTexture){
		mTextTexture = newTexture;
	}

	inline string getText(){
		return mText;
	}

	void setText(string newText, SDL_Color newColor);
};
#endif