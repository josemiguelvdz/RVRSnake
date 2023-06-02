#include "TextBox.h"

#include "../../Render/Window.h"
#include "../../Utils/Vector2.h"
#include "../../Scenes/SceneManager.h"
#include "../../Input/InputManager.h"
#include "../../Utils/SDLUtils.h"
#include "../../Utils/Timer.h"
#include "Text.h"

TextBox::TextBox(string btnTextureName, string text, int x, int y , int w, int h, int charLimit)
{
	mName = "textbox";
	
    mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

	mBtnTexture = &sdlutils().images().at(btnTextureName);

    mText = new Text(text, x + 10, y + 15);
	SDL_Color color = {0, 0, 0, 255};
	mText->setTexture(new Texture(window().getRenderer(), text, sdlutils().fonts().at("gameFont"), color));

	mIsWriting = false;

	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		lastFramePressed[i] = false;

	mCharLimit = charLimit;
}

TextBox::TextBox(Texture* btnTexture, Texture* textTexture, int x, int y , int w, int h, int charLimit)
{
	mPosX = x;
    mPosY = y;

    mWidth = mIniWidth = w;
    mHeight = mIniHeight = h;

    mBtnTexture = btnTexture;
    mText->setTexture(textTexture);

	mIsWriting = false;

	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		lastFramePressed[i] = false;

	mCharLimit = charLimit;
}

TextBox::~TextBox()
{
	delete mBtnTexture;
}

void TextBox::start()
{
	// UIButton::start();
}

void TextBox::update(const double& dt)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x >= mPosX && x < mPosX + mWidth && y >= mPosY && y < mPosY + mHeight) {
		if (inputManager().getButton("leftclick")) {
			mIsWriting = true;
		}
	}
	else{
		if (inputManager().getButton("leftclick")) {
			mIsWriting = false;
		}
	}

	if (mIsWriting){
		mNameBuffer = mText->getText();
		SDL_Event event;
		// Leer el teclado
        const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

        for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
			if (keyboardState[i]){
				char c;
				if (i >= 30 && i <= 39){ // NUMBERS
					// Number 0
					if (i == 39){
						c = i + 9;
					}
					else{
						c = i + 19;
					}

					if (c >= 48 && c <= 57 && !lastFramePressed[i] && mNameBuffer.size() <= mCharLimit){
						lastFramePressed[i] = true;
						mNameBuffer += c;
					}
				}
				else { // ALPHABET

					// PERIOD
					if (i == 55)
						c = i - 9;
					else
						c = i + 61;


					if (c >= 65 && c <= 90 && !lastFramePressed[i] && mNameBuffer.size() <= mCharLimit){
						lastFramePressed[i] = true;

						char newC = tolower(c);
						mNameBuffer += newC;
					}	

					if (c == 103 && !lastFramePressed[i]){ // delete last leter
						lastFramePressed[i] = true;

						if (mNameBuffer.size() > 1){
							mNameBuffer.pop_back();
						}
					}

					if (c == 46 && !lastFramePressed[i] && mNameBuffer.size() <= mCharLimit) { // PERIOD
						lastFramePressed[i] = true;
						mNameBuffer += c;
					}
				}	
			}
			else{
				lastFramePressed[i] = false;
			}
        }

		
		SDL_Color color = {0, 0, 0, 255};
		mText->setText(mNameBuffer, color);
	}
}

void TextBox::render(){
	if (mBtnTexture != nullptr){
        SDL_Rect textureBox = {mPosX, mPosY, mWidth, mHeight};
        mBtnTexture->render(textureBox);

        mText->render();
    }
}

void TextBox::setText(string text, SDL_Color color)
{
	mText->setText(text, color);
}

string TextBox::getText()
{
	return mText->getText();
}