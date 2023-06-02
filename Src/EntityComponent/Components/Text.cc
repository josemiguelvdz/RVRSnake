#include "Text.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Font.h"
#include "../../Utils/Texture.h"

Text::Text() : mText(""),
mPosX(0), mPosY(0)
{
    mName = "text";
}

Text::Text(string text, float posX, float posY) :
mText(text),
mPosX(posX), mPosY(posY)
{
    mName = "text";
}



Text::~Text()
{
}

void Text::start()
{
}

void Text::render(){
    /*
        RENDERIZAR 
    */
    mTextTexture->render(mPosX, mPosY);
}

void Text::update(const double& dt)
{
}

void Text::setText(string newText, SDL_Color newColor) {
    // Update Texture
    if (mTextTexture != nullptr)
        delete mTextTexture;

    mText = newText;
    mTextTexture = new Texture(window().getRenderer(), mText, sdlutils().fonts().at("gameFont"), newColor);
}
