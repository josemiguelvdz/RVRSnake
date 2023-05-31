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

	float mActualPosX;
	float mActualPosY;

	float mOriginalPosX;
	float mOriginalPosY;

	// Animation
	bool mSweeping;
	float mAmplitude = 13.f;
	float mPhase = 0.0f;

public:
	Image();
    Image(Texture* newTexture, int width, int height, float posX, float posY);
    Image(string textureName, int width, int height, float posX, float posY);
	~Image();
	void start() override;
	void update(const double& dt) override;
	void render() override;

	void playSimpleSweepAnim();
	void stopSimpleSweepAnim();
};
#endif