#include "HostGameButton.h"

#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/Battle.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"

HostGameButton::HostGameButton(string textureName, int x, int y , int w, int h)
{
    mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mBtnTexture = &sdlutils().images().at(textureName);
}

HostGameButton::HostGameButton(Texture* texture, int x, int y , int w, int h)
{
	mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

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

		if (inputManager().getButton("leftclick")) {
			//mClickAudio->play();
			execute();
			
		}
		// else if (stoppedSound) {
		// 	toggleSound = true;
		// 	stoppedSound = false;
		// 	if (mHoverAudio != nullptr)
		// 	mHoverAudio->play();
		// }
	}
	// else
	// 	toggleSound = false;
}

void HostGameButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void HostGameButton::toggleHover()
{
	// if (!toggleSound && !stoppedSound)
	// {
	// 	stoppedSound = true;
	// }
}

void HostGameButton::execute()
{
	// soundManager().stopEverySound();

    // Create game scene
	Scene* battleTest = new Battle(1);
	sceneManager().change(battleTest);
}
