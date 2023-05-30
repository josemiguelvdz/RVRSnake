// This file is part of the course TPV2@UCM - Samir Genaim

#include "SDLUtils.h"

#include <cassert>
#include <memory>

// #include "../../json/JSON.h"
//bool SDLUtils::sound_initialized = false;
// bool Music::sound_initialized = false;

SDLUtils::SDLUtils(){
}

SDLUtils::~SDLUtils() {
	//closeSDLExtensions();
	//closeWindow();
}


// void SDLUtils::closeWindow() {

// 	// destroy renderer and window
// 	SDL_DestroyRenderer(renderer_);
// 	SDL_DestroyWindow(window_);

// 	SDL_Quit(); // quit SDL
// }

void SDLUtils::initSDLExtensions() {
	std::cout << "Initializing SDL_ttf" << std::endl;
	// initialize SDL_ttf
	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);

	std::cout << "Initializing SDL_img" << std::endl;
	// initialize SDL_image
	int imgInit_ret = IMG_Init(
			IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	assert(imgInit_ret != 0);

	// std::cout << "Initializing SDL_Mixer" << std::endl;
	// initialize SDL_Mixer
	// int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	// if (mixOpenAudio == 0) {
	// 	int mixInit_ret = Mix_Init(
	// 		MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	// 	if (mixInit_ret != 0) {
	// 		//sound_initialized = true;
	// 		SoundEffect::sound_initialized = true;
	// 		Music::sound_initialized = true;
	// 		SoundEffect::setNumberofChannels(8); // we start with 8 channels
	// 	}
	
	// }
	
		
}

void SDLUtils::loadResources() {
	/*
		FONTS	
	*/

	/*
		IMAGES	
	*/
	images_.emplace("tileLight32", Texture(window().getRenderer(), "../../Resources/gfx/tile32_light.png"));
	images_.emplace("battleBackground", Texture(window().getRenderer(), "../../Resources/gfx/battleBg.jpeg"));
	images_.emplace("appleTemp", Texture(window().getRenderer(), "../../Resources/gfx/tile32_dark.png"));


	/*
		SOUNDS	
	*/

	std::cout << "Resources Loaded\n";

// 	// load fonts
// 	jValue = root["fonts"];
// 	if (jValue != nullptr) {
// 		if (jValue->IsArray()) {
// 			for (auto &v : jValue->AsArray()) {
// 				if (v->IsObject()) {
// 					JSONObject vObj = v->AsObject();
// 					std::string key = vObj["id"]->AsString();
// 					std::string file = vObj["file"]->AsString();
// 					uint8_t size =
// 							static_cast<uint8_t>(vObj["size"]->AsNumber());
// #ifdef _DEBUG
// 					std::cout << "Loading font with id: " << key << std::endl;
// #endif
// 					fonts_.emplace(key, Font(file, size));
// 				} else {
// 					throw "'fonts' array in '" + filename
// 							+ "' includes and invalid value";
// 				}
// 			}
// 		} else {
// 			throw "'fonts' is not an array in '" + filename + "'";
// 		}
// 	}

// 	// load sounds
// 	jValue = root["sounds"];
// 	if (jValue != nullptr) {
// 		if (jValue->IsArray()) {
// 			for (auto &v : jValue->AsArray()) {
// 				if (v->IsObject()) {
// 					JSONObject vObj = v->AsObject();
// 					std::string key = vObj["id"]->AsString();
// 					std::string file = vObj["file"]->AsString();
// #ifdef _DEBUG
// 					std::cout << "Loading sound effect with id: " << key
// 							<< std::endl;
// #endif
// 					sounds_.emplace(key, SoundEffect(file));
// 				} else {
// 					throw "'sounds' array in '" + filename
// 							+ "' includes and invalid value";
// 				}
// 			}
// 		} else {
// 			throw "'sounds' is not an array";
// 		}
// 	}

	// load musics
// 	jValue = root["musics"];
// 	if (jValue != nullptr) {
// 		if (jValue->IsArray()) {
// 			for (auto &v : jValue->AsArray()) {
// 				if (v->IsObject()) {
// 					JSONObject vObj = v->AsObject();
// 					std::string key = vObj["id"]->AsString();
// 					std::string file = vObj["file"]->AsString();
// #ifdef _DEBUG
// 					std::cout << "Loading music with id: " << key << std::endl;
// #endif
// 					musics_.emplace(key, Music(file));
// 				} else {
// 					throw "'musics' array in '" + filename
// 							+ "' includes and invalid value";
// 				}
// 			}
// 		} else {
// 			throw "'musics' is not an array";
// 		}
// 	}

// 	jValue = root["dialogs"];
// 	if (jValue != nullptr) {
// 		if (jValue->IsArray()) {
// 			for (auto& v : jValue->AsArray()) {
// 				if (v->IsObject()) {
// 					JSONObject vObj = v->AsObject();
// 					std::string key = vObj["id"]->AsString();
// 					std::string file = vObj["file"]->AsString();
// #ifdef _DEBUG
// 					std::cout << "Loading dialog with id: " << key << std::endl;
// #endif
// 					dialogos.emplace(key, file);
// 				}
// 				else {
// 					throw "'dialogs' array in '" + filename
// 						+ "' includes and invalid value";
// 				}
// 			}
// 		}
// 		else {
// 			throw "'dialogs' is not an array in '" + filename + "'";
// 		}
// 	}

// 	// load anims
// 	jValue = root["anims"];
// 	if (jValue != nullptr) {
// 		if (jValue->IsArray()) {
// 			for (auto& v : jValue->AsArray()) {
// 				if (v->IsObject()) {
// 					JSONObject vObj = v->AsObject();
// 					std::string key = vObj["id"]->AsString();
// 					std::string file = vObj["file"]->AsString();
// 					uint8_t length = static_cast<uint8_t>(vObj["length"]->AsNumber());
// 					uint8_t sheetWidth = static_cast<uint8_t>(vObj["sheetWidth"]->AsNumber());
// 					uint8_t sheetHeight = static_cast<uint8_t>(vObj["sheetLength"]->AsNumber());
// 					int spriteWidth = static_cast<int>(vObj["spriteWidth"]->AsNumber());
// 					int spriteHeight = static_cast<int>(vObj["spriteHeight"]->AsNumber());
// 					uint8_t padding = static_cast<uint8_t>(vObj["padding"]->AsNumber());
// #ifdef _DEBUG
// 					std::cout << "Loading anim with id: " << key << std::endl;
// #endif
// 					anims_.emplace(key, Texture(renderer(), file));
// 				}
// 				else {
// 					throw "'anims' array in '" + filename
// 						+ "' includes and invalid value";
// 				}
// 			}
// 		}
// 		else {
// 			throw "'anims' is not an array in '" + filename + "'";
// 		}
// 	}
	
}


void SDLUtils::closeSDLExtensions() {

	//musics_.clear();
	// sounds_.clear();
	images_.clear();
	fonts_.clear();
	msgs_.clear();

	// Mix_Quit(); // quit SDL_mixer
	IMG_Quit(); // quit SDL_image
	TTF_Quit(); // quit SDL_ttf
}
