// This file is part of the course TPV2@UCM - Samir Genaim

#include "SDLUtils.h"

#include <cassert>
#include <memory>

SDLUtils::SDLUtils(){
}

SDLUtils::~SDLUtils() {
	closeSDLExtensions();
}

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
	std::cout << "Finished initialization of libraries\n";
		
}

void SDLUtils::loadResources() {
	/*
		FONTS	
	*/
	fonts_.emplace("gameFont", Font("../../Resources/font/font.ttf", 48));		

	/*
		IMAGES	
	*/
	images_.emplace("tileLight32", Texture(window().getRenderer(), "../../Resources/gfx/tile32_light.png"));
	images_.emplace("battleBackground", Texture(window().getRenderer(), "../../Resources/gfx/battleBg.jpeg"));
	images_.emplace("appleTemp", Texture(window().getRenderer(), "../../Resources/gfx/tile32_dark.png"));
	images_.emplace("gameLogo", Texture(window().getRenderer(), "../../Resources/gfx/gameLogo.png"));
	images_.emplace("snakeTexture", Texture(window().getRenderer(), "../../Resources/gfx/snake.png"));
	images_.emplace("authorsBg", Texture(window().getRenderer(), "../../Resources/gfx/authorsBg.png"));
	images_.emplace("singleplayerButton", Texture(window().getRenderer(), "../../Resources/gfx/singleplayerButton.png"));
	images_.emplace("multiplayerButton", Texture(window().getRenderer(), "../../Resources/gfx/multiplayerButton.png"));
	images_.emplace("networkMenuBg", Texture(window().getRenderer(), "../../Resources/gfx/menuBg.png"));
	images_.emplace("networkMenuDeco", Texture(window().getRenderer(), "../../Resources/gfx/menuNetworkDeco.png"));
	images_.emplace("hostButton", Texture(window().getRenderer(), "../../Resources/gfx/hostGameButton.png"));
	images_.emplace("joinButton", Texture(window().getRenderer(), "../../Resources/gfx/joinGameButton.png"));
	images_.emplace("textBox", Texture(window().getRenderer(), "../../Resources/gfx/textBox.png"));
	images_.emplace("nameBg", Texture(window().getRenderer(), "../../Resources/gfx/nameBg.png"));
	images_.emplace("colorSelectionDeco", Texture(window().getRenderer(), "../../Resources/gfx/colorSelectionDeco.png"));
	images_.emplace("connectedIcon", Texture(window().getRenderer(), "../../Resources/gfx/connectedIcon.png"));
	images_.emplace("disconnectedIcon", Texture(window().getRenderer(), "../../Resources/gfx/disconnectedIcon.png"));
	images_.emplace("redColorDeco", Texture(window().getRenderer(), "../../Resources/gfx/redColorDeco.png"));
	images_.emplace("blueColorDeco", Texture(window().getRenderer(), "../../Resources/gfx/blueColorDeco.png"));
	images_.emplace("yellowColorDeco", Texture(window().getRenderer(), "../../Resources/gfx/yellowColorDeco.png"));
	images_.emplace("purpleColorDeco", Texture(window().getRenderer(), "../../Resources/gfx/purpleColorDeco.png"));
	images_.emplace("grayColorDeco", Texture(window().getRenderer(), "../../Resources/gfx/grayColorDeco.png"));
	images_.emplace("redButton", Texture(window().getRenderer(), "../../Resources/gfx/redButton.png"));
	images_.emplace("blueButton", Texture(window().getRenderer(), "../../Resources/gfx/blueButton.png"));
	images_.emplace("yellowButton", Texture(window().getRenderer(), "../../Resources/gfx/yellowButton.png"));
	images_.emplace("purpleButton", Texture(window().getRenderer(), "../../Resources/gfx/purpleButton.png"));
	images_.emplace("grayButton", Texture(window().getRenderer(), "../../Resources/gfx/grayButton.png"));
	

	/*
		SOUNDS	
	*/

	std::cout << "Resources Loaded\n";
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

