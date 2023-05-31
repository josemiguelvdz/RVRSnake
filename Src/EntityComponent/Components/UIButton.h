#pragma once

#ifndef __ENTITYCOMPONENT_UI_BUTTON
#define __ENTITYCOMPONENT_UI_BUTTON

#include "Component.h"

using namespace std;

class Texture;

class UIButton : public Component
{
protected:
	Texture* mBtnTexture;

    float mPosX;
    float mPosY;

    float mWidth;
    float mHeight;

    float mIniWidth;
    float mIniHeight;

    float mMaxWidth;
    float mMaxHeight;

    bool mIsHover;
public:
	UIButton();
    ~UIButton();

	virtual void execute();
    virtual void start();
	virtual void update(const double& dt);
    virtual void render();

    inline Texture* getTexture(){
		return mBtnTexture;
	}
};

#endif