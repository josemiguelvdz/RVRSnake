#include "JoinGameButton.h"

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

JoinGameButton::JoinGameButton(string textureName, int x, int y , int w, int h)
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

JoinGameButton::JoinGameButton(Texture* texture, int x, int y , int w, int h)
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

JoinGameButton::~JoinGameButton()
{
	delete mBtnTexture;
}

void JoinGameButton::start()
{
	// Get reference to IP Text box
    ipTextBox = mEntity->getScene()->findEntity("IpTextBox").get()->getComponent<TextBox>("textbox");
}

void JoinGameButton::update(const double& dt)
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

    // opacity
    opacityUpdate();
}

void JoinGameButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void JoinGameButton::initClickAnimation()
{
	// soundManager().stopEverySound();
	mWidth = mIniWidth;
	mHeight = mIniHeight;

	mExecuteTimer->resume();
}

void JoinGameButton::execute()
{
	mExecuteTimer->reset();
	mExecuteTimer->pause();

	// soundManager().stopEverySound();
	string name = mEntity->getScene()->findEntity("NameTextBox").get()->getComponent<TextBox>("textbox")->getText();
	name = name.substr(1, name.size() - 1);
	gameManager()->myName = name;

	string ip = ipTextBox->getText();
	ip = ip.substr(1, ip.size() - 1);

	networkManager().init(false, ip.c_str());
}

void JoinGameButton::opacityUpdate() {
    // std::cout << ipTextBox->getText() << "\n";
    if (ipTextBox->getText().size() > 7)
        SDL_SetTextureAlphaMod(mBtnTexture->getSdlTexture(), 255);
    else
        SDL_SetTextureAlphaMod(mBtnTexture->getSdlTexture(), 0);
}