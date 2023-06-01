#include "SinglePlayerButton.h"

#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/Battle.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"

SinglePlayerButton::SinglePlayerButton(string textureName, int x, int y , int w, int h)
{
    mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 20;
	mMaxHeight = mHeight + 10;

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
			//mClickAudio->play();
			execute();	
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
}

void SinglePlayerButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void SinglePlayerButton::execute()
{
	// soundManager().stopEverySound();

    // Create game scene
	Scene* battleTest = new Battle(1);
	sceneManager().change(battleTest);
}

