#include "Image.h"
#include "../../Render/Window.h"
#include "../Entity.h"

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"

Image::Image() : mName("image"), mIMGTexture(nullptr),  mTextureWidth(0), mTextureHeight(0), mIMGPosX(0), mIMGPosY(0)
{
}

Image::Image(Texture* newTexture, int width, int height, int posX, int posY) : mName("image"), 
mIMGTexture(newTexture),  
mTextureWidth(width), 
mTextureHeight(height),
mIMGPosX(posX), 
mIMGPosY(posY)
{
}

Image::Image(string textureName, int width, int height, int posX, int posY) : mName("image"), 
mTextureWidth(width), 
mTextureHeight(height),
mIMGPosX(posX), 
mIMGPosY(posY)
{
    mIMGTexture = &sdlutils().images().at(textureName);
}



Image::~Image()
{
    delete mIMGTexture;
}

void Image::start()
{
    // Load
}

void Image::render(){
    /*
        RENDERIZAR 
    */
    if (mIMGTexture != nullptr){
        SDL_Rect textureBox = {mIMGPosX, mIMGPosY, mTextureWidth, mTextureHeight};
        mIMGTexture->render(textureBox);
    }
}

void Image::update(const double& dt)
{

}
