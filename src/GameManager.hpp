#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include <TextureObject.hpp>
#include <Sprite.hpp>
#include <MultiSprite.hpp>
#include <ClickableObject.hpp>
#include <TextObject.hpp>
#include <CrossSystemFunctions.hpp>

class GameManager
{
	public:
		GameManager();
		~GameManager();
		void run();
	private:
		void initializeSDL();
		
		//screen resolution
		int _screenWidth;
		int _screenHeight;
		
		bool _SDLInitialisation; 
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		
		std::string _pathToSourceFolder;
};




#endif
