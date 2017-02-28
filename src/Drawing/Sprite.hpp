#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>

#include "TextureObject.hpp"

/**
* Sprite class
*/
class Sprite
{	
	public:
		Sprite();
		Sprite(std::string pathToFile, SDL_Renderer *rendererData);
		Sprite(const Sprite &obj);
		Sprite& operator=(const Sprite& obj);
		~Sprite();
		void render(int newXPosition, int newYPosition);
		void render();
		void setXPosition(int newXPosition);
		void setYPosition(int newYPosition);
		void setPosition(int newXPosition, int newYPosition);
		int getXPosition();
		int getYPosition();
		int getTextureWidth();
		int getTextureHeight();
	protected:
		TextureObject* getActualTexture();
	private:
		TextureObject _actualTexture;
		int _xPositionOnScreen;
		int _yPositionOnScreen;
};

#endif
