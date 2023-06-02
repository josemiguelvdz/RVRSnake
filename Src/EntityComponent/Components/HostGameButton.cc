#include "HostGameButton.h"

#include "GameManager.h"
#include "TextBox.h"
#include "../Entity.h"
#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/ColorSelection.h"
#include "../../Input/InputManager.h"
#include "../../Network/NetworkManager.h"
#include "../../Utils/SDLUtils.h"
#include "../../Utils/Timer.h"

HostGameButton::HostGameButton(string textureName, int x, int y , int w, int h)
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

HostGameButton::HostGameButton(Texture* texture, int x, int y , int w, int h)
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

void HostGameButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void HostGameButton::initClickAnimation()
{
	// soundManager().stopEverySound();
	mWidth = mIniWidth;
	mHeight = mIniHeight;

	mExecuteTimer->resume();
}

void HostGameButton::execute()
{
	// soundManager().stopEverySound();

	gameManager()->myName = mEntity->getScene()->findEntity("NameTextBox").get()->getComponent<TextBox>("textbox")->getText();
	networkManager().init(true, nullptr);
	
    // Create game scene
	Scene* colorSelection = new ColorSelection();
	sceneManager().change(colorSelection);
}
