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

	mBtnTexture = &sdlutils().images().at(textureName);
}

SinglePlayerButton::SinglePlayerButton(Texture* texture, int x, int y , int w, int h)
{
	mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

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

		// if (inputManager().getButton("LEFTCLICK")) {
		// 	//mClickAudio->play();
		// 	execute();

        //     std::cout << "CLICK\n";
		// }
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

void SinglePlayerButton::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);
    }
}

void SinglePlayerButton::toggleHover()
{
	// if (!toggleSound && !stoppedSound)
	// {
	// 	stoppedSound = true;
	// }
}

void SinglePlayerButton::execute()
{
	// soundManager().stopEverySound();

    // Create game scene
	Scene* battleTest = new Battle(1);
	sceneManager().loadScene(battleTest);
}

