#include <TextObject.hpp>

//~ TTF_Font* TextObject::_defaultFont = nullptr;

TextObject::TextObject()
: _hasTexture(false), _texture(nullptr), _textureWidth(0), _textureHeight(0), _font(nullptr), _xPositionOnScreen(0), _yPositionOnScreen(0), _pathToFontFile(""), _renderer(nullptr), _fontSize(16), _fontColor(SDL_Color())
{
	
}

TextObject::TextObject(const std::string &pathToFontFile, SDL_Renderer* rendererObject, const std::string &message, int fontSize, SDL_Color fontColor)
: _hasTexture(false), _texture(nullptr), _textureWidth(0), _textureHeight(0), _font(nullptr), _xPositionOnScreen(0), _yPositionOnScreen(0), _pathToFontFile(pathToFontFile), _renderer(nullptr), _fontSize(fontSize), _fontColor(fontColor)
{
	this->_renderer = rendererObject;
	this->_pathToFontFile = pathToFontFile;
	this->loadFont();
	this->loadMessageTexture(message);
}

TextObject::~TextObject()
{
	if(this->_font != nullptr)
	{
		TTF_CloseFont(this->_font);
		this->_font == nullptr;
	}
	
	if(this->_texture != nullptr)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture == nullptr;
	}
}

void TextObject::loadFont()
{
	if(this->_font != nullptr)
	{
		TTF_CloseFont(this->_font);
		this->_font = nullptr;
		this->_font = TTF_OpenFont(this->_pathToFontFile.c_str(), this->_fontSize);
		if(this->_font == nullptr)
		{
			std::cout<<"TTF_OpenFont error"<<std::endl;
		}
	}
	else
	{
		this->_font = TTF_OpenFont(this->_pathToFontFile.c_str(), this->_fontSize);
		if(this->_font == nullptr)
		{
			std::cout<<"TTF_OpenFont error"<<std::endl;
		}
	}
}

void TextObject::loadMessageTexture(const std::string &message)
{
	if(this->_hasTexture)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture = nullptr;
		this->_hasTexture = false;
	}
	
	SDL_Surface* textOnSurface = TTF_RenderText_Blended(this->_font, message.c_str(), this->_fontColor);
	if(textOnSurface == nullptr)
	{
		std::cout<<"LoadMessageTexture error"<<std::endl;
	}
	else
	{	
		this->_texture = SDL_CreateTextureFromSurface(this->_renderer, textOnSurface);
		SDL_FreeSurface(textOnSurface);
		if (this->_texture == nullptr)
		{
			std::cout<<"LoadMessageTexture error"<<std::endl;
		}
		else
		{
			this->_hasTexture = true;
			SDL_QueryTexture(this->_texture, NULL, NULL, &this->_textureWidth, &this->_textureHeight);
		}
	}
}

void TextObject::loadMessageTexture(const std::string &message, int fontSize)
{
	this->_fontSize = fontSize;
	this->loadFont();
	this->loadMessageTexture(message);
}

void TextObject::loadMessageTexture(const std::string &message, SDL_Color fontColor)
{
	this->_fontColor = fontColor;
	this->loadFont();
	this->loadMessageTexture(message);
}

void TextObject::loadMessageTexture(const std::string &message, int fontSize, SDL_Color fontColor)
{
	this->_fontSize = fontSize;
	this->_fontColor = fontColor;
	this->loadFont();
	this->loadMessageTexture(message);
}

void TextObject::render()
{
	if(this->_hasTexture)
	{
		SDL_Rect clipPositionOnScreen;
		clipPositionOnScreen.x = this->_xPositionOnScreen;
		clipPositionOnScreen.y = this->_yPositionOnScreen;
		clipPositionOnScreen.w = this->_textureWidth;
		clipPositionOnScreen.h = this->_textureHeight;
		SDL_RenderCopy(this->_renderer, this->_texture, NULL, &clipPositionOnScreen);
		//~ SDL_RenderCopy(this->_renderer, this->_texture, NULL, NULL);
	}
}
