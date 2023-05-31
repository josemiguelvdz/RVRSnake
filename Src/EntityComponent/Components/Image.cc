#include "Image.h"
#include "../../Render/Window.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"
#include "../../Utils/SimpleLerp.h"

Image::Image() : mName("image"), mIMGTexture(nullptr), 
mTextureWidth(0), mTextureHeight(0), 
mOriginalPosX(0.f), mOriginalPosY(0.f), 
mSweeping(false), mActualPosX(0.f),
mActualPosY(0.f)
{
}

Image::Image(Texture* newTexture, int width, int height, float posX, float posY) : mName("image"), 
mIMGTexture(newTexture),  
mTextureWidth(width), mTextureHeight(height),
mOriginalPosX(posX), mOriginalPosY(posY), 
mSweeping(false), mActualPosX(posX),
mActualPosY(posY)
{
}

Image::Image(string textureName, int width, int height, float posX, float posY) : mName("image"), 
mTextureWidth(width), mTextureHeight(height),
mOriginalPosX(posX), mOriginalPosY(posY), 
mSweeping(false), mActualPosX(posX),
mActualPosY(posY)
{
    mIMGTexture = &sdlutils().images().at(textureName);
}



Image::~Image()
{
    delete mIMGTexture;
}

void Image::start()
{
}

void Image::render(){
    /*
        RENDERIZAR 
    */
    if (mIMGTexture != nullptr){
        SDL_Rect textureBox = {mActualPosX, mActualPosY, mTextureWidth, mTextureHeight};
        mIMGTexture->render(textureBox);
    }
}

void Image::update(const double& dt)
{
    if (mSweeping){
        // Calcula la posición vertical utilizando la función seno
        float offsetY = mAmplitude * SDL_sin(mPhase) * dt;

        if (dt > 0 && dt < 1)
            mPhase += dt;

        mActualPosY += offsetY;
    }
}

void Image::playSimpleSweepAnim(){
    mSweeping = true;
}

void Image::stopSimpleSweepAnim(){
    mSweeping = false;
}
