// This file is part of the course TPV2@UCM - Samir Genaim

#include "Texture.h"

#include "SimpleLerp.h"
#include "Timer.h"

Texture& Texture::operator=(Texture&& other) noexcept {
	this->~Texture();
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;

	appearTimer = other.appearTimer;
	disappearTimer = other.disappearTimer;

	return *this;
}

Texture::Texture(Texture&& other) noexcept {
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;

	appearTimer = other.appearTimer;
	disappearTimer = other.disappearTimer;
}

Texture::Texture(SDL_Renderer* renderer, const std::string& fileName) {
	assert(renderer != nullptr);

	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(surface);
		throw "Couldn't load image: " + fileName;
	}

	width_ = surface->w;
	height_ = surface->h;
	renderer_ = renderer;

	SDL_FreeSurface(surface);

	appearTimer = new Timer(false);
	disappearTimer = new Timer(false);
}

Texture::Texture(SDL_Renderer* renderer, const std::string& text,
	const Font& font, const SDL_Color& fgColor) {
	constructFromText(renderer, text, font, &fgColor);
}

Texture::Texture(SDL_Renderer* renderer, const std::string& text,
	const Font& font, const SDL_Color& fgColor, const SDL_Color& bgColor) {
	constructFromText(renderer, text, font, &fgColor, &bgColor);
}

Texture::Texture(SDL_Renderer* rend, SDL_Texture* tex, int width, int height)
{
	renderer_ = rend;
	texture_ = tex;
	width_ = width;
	height_ = height;

	appearTimer = new Timer(false);
	disappearTimer = new Timer(false);
}

void Texture::constructFromText(SDL_Renderer* renderer, const std::string& text,
	const Font& font, const SDL_Color* fgColor, const SDL_Color* bgColor) {
	assert(renderer != nullptr);

	SDL_Surface* textSurface =
		bgColor == nullptr ?
		font.renderText(text, *fgColor) :
		font.renderText(text, *fgColor, *bgColor);

	if (textSurface == nullptr)
		throw "Couldn't create text: " + text;

	texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(textSurface);
		throw "Couldn't create text: " + text;
	}

	width_ = textSurface->w;
	height_ = textSurface->h;
	renderer_ = renderer;

	SDL_FreeSurface(textSurface);

	appearTimer = new Timer(false);
	disappearTimer = new Timer(false);
}

void Texture::textureUpdate() {
	appearTimer->update(0.016);
	disappearTimer->update(0.016);

	if (appearTimer->getRawSeconds() > delayAppear){
		if (isAppearing){
			// Interpolate to 255 opacity
			Uint8 currAlpha;
			SDL_GetTextureAlphaMod(texture_, &currAlpha);

			Uint8 newAlpha = currAlpha + (Uint8) 1;

			if (newAlpha >= 255){
				isAppearing = false;
				appearTimer->pause();
				appearTimer->reset();
			}

			SDL_SetTextureAlphaMod(texture_, newAlpha);
		}
	}

	if (disappearTimer->getRawSeconds() > delayDisappear){
		if (isDisappearing){
			// Interpolate to 0 opacity
			Uint8 currAlpha;
			SDL_GetTextureAlphaMod(texture_, &currAlpha);

			Uint8 newAlpha = currAlpha - (Uint8) 1;

			if (newAlpha <= 0){
				isDisappearing = false;
				disappearTimer->pause();
				disappearTimer->reset();
			}

			SDL_SetTextureAlphaMod(texture_, newAlpha);
		}
	}
}

void Texture::startToAppear(float delay){
	// Start
	delayAppear = delay;
	isAppearing = true;

	appearTimer->resume();
}

void Texture::startToDissappear(float delay){
	// Start
	delayDisappear = delay;
	isDisappearing = true;

	disappearTimer->resume();
}
