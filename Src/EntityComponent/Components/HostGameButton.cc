#include "HostGameButton.h"

#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/ColorSelection.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"

HostGameButton::HostGameButton(string textureName, int x, int y , int w, int h)
{
    mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 10;
	mMaxHeight = mHeight + 10;

	mBtnTexture = &sdlutils().images().at(textureName);
}

HostGameButton::HostGameButton(Texture* texture, int x, int y , int w, int h)
{
	mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 10;
	mMaxHeight = mHeight + 10;

    mBtnTexture = texture;
}

HostGameButton::~HostGameButton()
{
	delete mBtnTexture;
}

void HostGameButton::start()
{
	// UIButton::start();
}

void HostGameButton::update(const double& dt)
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

void HostGameButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void HostGameButton::execute()
{
	// soundManager().stopEverySound();

    // Create game scene
	Scene* colorSelection = new ColorSelection();
	sceneManager().change(colorSelection);
}
