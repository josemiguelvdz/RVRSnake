#include "SinglePlayerButton.h"

#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/Battle.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"
#include "../../Utils/Timer.h"

SinglePlayerButton::SinglePlayerButton(string textureName, int x, int y , int w, int h)
{
    mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 20;
	mMaxHeight = mHeight + 10;

	mDelayExecution = 0.6f;
	mExecuteTimer = new Timer(false);

	mBtnTexture = &sdlutils().images().at(textureName);
}

SinglePlayerButton::SinglePlayerButton(Texture* texture, int x, int y , int w, int h)
{
	mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 20;
	mMaxHeight = mHeight + 10;

	mDelayExecution = 0.6f;
	mExecuteTimer = new Timer(false);

    mBtnTexture = texture;
}

SinglePlayerButton::~SinglePlayerButton()
{
	delete mBtnTexture;
}

void SinglePlayerButton::start()
{
	// UIButton::start();
}

void SinglePlayerButton::update(const double& dt)
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

void SinglePlayerButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void SinglePlayerButton::initClickAnimation()
{
	// soundManager().stopEverySound();
	mWidth = mIniWidth;
	mHeight = mIniHeight;

	mExecuteTimer->resume();
}

void SinglePlayerButton::execute()
{
    // Create game scene
	//Scene* battleTest = new Battle(1);
	Scene* battleTest = new Battle(4);
	sceneManager().change(battleTest);
}

