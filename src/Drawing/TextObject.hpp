#ifndef TEXT_OBJECT_HPP
#define TEXT_OBJECT_HPP

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class TextObject
{
	public:
		TextObject();
		TextObject(const std::string &pathToFile, SDL_Renderer* rendererObject, const std::string &message = "", int fontSize = 16, SDL_Color fontColor = SDL_Color());
		~TextObject();
		void loadMessageTexture(const std::string &message);
		void loadMessageTexture(const std::string &message, int fontSize);
		void loadMessageTexture(const std::string &message, SDL_Color fontColor);
		void loadMessageTexture(const std::string &message, int fontSize, SDL_Color fontColor);
		void render();
		int getTextureWidth();
		int getTextureHeight();
		void setPositionOnScreen(int xPositionOnScreen, int yPositionOnScreen);
	private:
		void loadFont();
		std::string _pathToFontFile;
		SDL_Color _fontColor;
		int _fontSize;
		SDL_Renderer* _renderer;
		bool _hasTexture;
		SDL_Texture* _texture;
		int _xPositionOnScreen;
		int _yPositionOnScreen;
		int _textureWidth;
		int _textureHeight;
		TTF_Font* _font;
};

#endif
