#include "Text.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Font.h"
#include "../../Utils/Texture.h"

Text::Text() : mName("text"), mText(""),
mPosX(0), mPosY(0)
{
}

Text::Text(string text, float posX, float posY) :
mName("text"), mText(text),
mPosX(posX), mPosY(posY)
{
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