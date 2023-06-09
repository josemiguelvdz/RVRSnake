#include "MultiPlayerButton.h"

#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/OnlineSelection.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"
#include "../../Utils/Timer.h"

MultiPlayerButton::MultiPlayerButton(string textureName, int x, int y , int w, int h)
{
    mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 20;
	mMaxHeight = mHeight + 10;

	mIsHover = false;

	mDelayExecution = 0.6f;
	mExecuteTimer = new Timer(false);

	mBtnTexture = &sdlutils().images().at(textureName);
}

MultiPlayerButton::MultiPlayerButton(Texture* texture, int x, int y , int w, int h)
{
	mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 20;
	mMaxHeight = mHeight + 10;

	mIsHover = false;

	mDelayExecution = 0.6f;
	mExecuteTimer = new Timer(false);

    mBtnTexture = texture;
}

MultiPlayerButton::~MultiPlayerButton()
{
	delete mBtnTexture;
}

void MultiPlayerButton::start()
{
	// UIButton::start();
}

void MultiPlayerButton::update(const double& dt)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x >= mPosX && x < mPosX + mWidth && y >= mPosY && y < mPosY + mHeight) {
		setHover(true);

		if (inputManager().getButton("leftclick")) {
			Uint8 opacity = 0;
			SDL_GetTextureAlphaMod(mBtnTexture->getSdlTexture(), &opacity);

			if (opacity == 255)
				initClickAnimation();	
		}
	}
	else{
		setHover(false);
	}
	

	// Hover Anim
	if (mIsHover){
		mWidth = SimpleLerp::Lerp(mWidth, mMaxWidth, 0.1);
		mHeight = SimpleLerp::Lerp(mHeight, mMaxHeight, 0.1);
	}
	else{
		mWidth = SimpleLerp::Lerp(mWidth, mIniWidth, 0.1);
		mHeight = SimpleLerp::Lerp(mHeight, mIniHeight, 0.1);
	}

	mExecuteTimer->update(dt);

	// Click Action
	if (mExecuteTimer->getRawSeconds() > mDelayExecution){
		execute();
	}
}

void MultiPlayerButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void MultiPlayerButton::initClickAnimation()
{
	// soundManager().stopEverySound();
	mWidth = mIniWidth;
	mHeight = mIniHeight;

	mExecuteTimer->resume();
}

void MultiPlayerButton::execute()
{
    // Create game scene
	Scene* onlineSelection = new OnlineSelection();
	sceneManager().change(onlineSelection);
}
