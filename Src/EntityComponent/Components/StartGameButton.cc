#include "StartGameButton.h"

#include "GameManager.h"
#include "TextBox.h"
#include "../Entity.h"
#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/Battle.h"
#include "../../Input/InputManager.h"
#include "../../Network/NetworkManager.h"
#include "../../Utils/SDLUtils.h"
#include "../../Utils/Timer.h"

StartGameButton::StartGameButton(string textureName, int x, int y , int w, int h)
{
    mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 10;
	mMaxHeight = mHeight + 10;

	mDelayExecution = 0.6f;
	mExecuteTimer = new Timer(false);

	mBtnTexture = &sdlutils().images().at(textureName);
}

StartGameButton::StartGameButton(Texture* texture, int x, int y , int w, int h)
{
	mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mMaxWidth = mWidth + 10;
	mMaxHeight = mHeight + 10;

	mDelayExecution = 0.6f;
	mExecuteTimer = new Timer(false);

    mBtnTexture = texture;
}

StartGameButton::~StartGameButton()
{
	delete mBtnTexture;
}

void StartGameButton::start()
{
}

void StartGameButton::update(const double& dt)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x >= mPosX && x < mPosX + mWidth && y >= mPosY && y < mPosY + mHeight) {
		setHover(true);

		if (inputManager().getButton("leftclick")) {
			//mClickAudio->play();
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

void StartGameButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void StartGameButton::initClickAnimation()
{
	// soundManager().stopEverySound();
	mWidth = mIniWidth;
	mHeight = mIniHeight;

	mExecuteTimer->resume();
}

void StartGameButton::execute()
{
	networkManager().sendStartGame();

	Scene* battleTest = new Battle(networkManager().getNumberConnectedPlayers());
	sceneManager().change(battleTest);
}
