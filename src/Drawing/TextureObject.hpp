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
		TextureObject(const TextureObject &obj);
		TextureObject& operator=(const TextureObject& obj);
		void render();
		void render(SDL_Rect* clipPositionOnScreen);
		void render(SDL_Rect* clipPositionOnScreen, SDL_Rect* clipPositionOnTexture);
		bool loadTexture(const std::string &pathToFile, SDL_Renderer* rendererObject);
		bool loadTexture(const std::string &pathToFile);
		int getTextureWidth();
		int getTextureHeight();
	private:
		std::string _pathToFile;
		bool _hasTexture;
		SDL_Renderer* _renderer;
		SDL_Texture* _texture;
		int _textureWidth;
		int _textureHeight;
};

#endif
