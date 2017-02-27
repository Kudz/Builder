#ifndef TEXTURE_OBJECT_HPP
#define TEXTURE_OBJECT_HPP

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

class TextureObject
{
	public:
		TextureObject();
		TextureObject(const std::string &pathToFile, SDL_Renderer* rendererObject);
		~TextureObject();
		void render();
		bool loadTexture(const std::string &pathToFile, SDL_Renderer* rendererObject);
		bool loadTexture(const std::string &pathToFile);
	private:
		bool _hasTexture;
		SDL_Renderer* _renderer;
		SDL_Texture* _texture;
};




#endif
