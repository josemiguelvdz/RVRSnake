#pragma once

#ifndef __ENTITYCOMPONENT_IMAGE
#define __ENTITYCOMPONENT_IMAGE

#include "Component.h"
#include <string>
#include <vector>

using namespace std;

class Texture;

class Image : public Component
{
private:
protected:
	std::string mName;
    Texture* mIMGTexture;

	int mTextureWidth;
	int mTextureHeight;

	int mIMGPosX;
	int mIMGPosY;
public:
	Image();
    Image(Texture* newTexture, int width, int height, int posX, int posY);
    Image(string textureName, int width, int height, int posX, int posY);
	~Image();
	void start() override;
	void update(const double& dt) override;
	void render() override;
};
#endif