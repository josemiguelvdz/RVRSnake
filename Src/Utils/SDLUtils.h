#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "Singleton.h"
#include "RandomNumberGenerator.h"
#include "Font.h"
#include "Texture.h"
#include "VirtualTimer.h"

#include "../Render/Window.h"

class SDLUtils: public Singleton<SDLUtils> {

	friend Singleton<SDLUtils> ; // needed to give access to private constructors
	//static bool sound_initialized;
public:
	template<typename T>
	using sdl_resource_table = std::map<std::string,T>;

	~SDLUtils();

	// clear the renderer with a given SDL_Color
	inline void clearRenderer(SDL_Color bg = build_sdlcolor(0x7F7F7F)) {
		SDL_SetRenderDrawColor(window().getRenderer(), COLOREXP(bg));
		SDL_RenderClear(window().getRenderer());
	}

	// present the current content of the renderer
	inline void presentRenderer() {
		SDL_RenderPresent(window().getRenderer());
	}


	// show the cursor when mouse is over the window
	inline void showCursor() {
		SDL_ShowCursor(1);
	}

	// hide the cursor when mouse is over the window
	inline void hideCursor() {
		SDL_ShowCursor(0);
	}

	// All resource maps can be modified from outside, this way you can store
	// your own dynamically. Be careful when modifying them!

	// fonts map
	inline sdl_resource_table<Font>& fonts() {
		return fonts_;
	}

	// images map
	inline sdl_resource_table<Texture>& images() {
		return images_;
	}

	// messages map
	inline sdl_resource_table<Texture>& messages() {
		return msgs_;
	}

	// messages map
	inline sdl_resource_table<Texture>& tilesets() {
		return tilesets_;
	}

	// sound effects map
	// inline sdl_resource_table<SoundEffect>& soundEffects() {
	// 	return sounds_;
	// }

	// // musics maps
	// inline sdl_resource_table<Music>& musics() {
	// 	return musics_;
	// }

	/*
	// anims map
	inline sdl_resource_table<Texture>& anims() {
		return anims_;
	}
	*/

	// Access to the random number generator. It is important to always
	// use this generator, this way you can regenerate the same sequence
	// if you start from the same seed
	inline RandomNumberGenerator& rand() {
		return random_;
	}

	// Access to the virtual timer, it is useful when you allow to 'pause'
	// your game, also for synchronising clocks of players (when using sdlnet)
	inline VirtualTimer& virtualTimer() {
		return timer_;
	}

	// Access to real time
	inline Uint32 currRealTime() const {
		return SDL_GetTicks();
	}

	void initSDLExtensions(); // initialize resources (fonts, textures, audio, etc.)
	void closeSDLExtensions(); // free resources the
	void loadResources(); // load resources

private:
	SDLUtils();

	sdl_resource_table<Font> fonts_; // fonts map (string -> font)
	sdl_resource_table<Texture> images_; // textures map (string -> texture)
	sdl_resource_table<Texture> tilesets_; // textures map (string -> texture)
	sdl_resource_table<Texture> msgs_; // textures map (string -> texture)
	//sdl_resource_table<SoundEffect> sounds_; // sounds map (string -> sound)
	//sdl_resource_table<Music> musics_; // musics map (string -> music)
	// sdl_resource_table<Texture> anims_; // anims map (string -> anim)

	RandomNumberGenerator random_; // (pseudo) random numbers generator
	VirtualTimer timer_; // virtual timer
};


// This macro defines a compact way for using the singleton SDLUtils, instead of
// writing SDLUtils::instance()->method() we write sdlutils().method()
//
inline SDLUtils& sdlutils() {
	return *SDLUtils::Instance();
}
