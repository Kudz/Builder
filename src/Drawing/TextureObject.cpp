#include <TextureObject.hpp>

TextureObject::TextureObject()
: _hasTexture(false), _texture(nullptr), _renderer(nullptr), _pathToFile(""), _textureWidth(0), _textureHeight(0)
{
	
}

TextureObject::TextureObject(const std::string &pathToFile, SDL_Renderer* rendererObject)
: _hasTexture(false), _texture(nullptr), _renderer(nullptr), _pathToFile(pathToFile)
{
	this->loadTexture(pathToFile, rendererObject);
	SDL_QueryTexture(this->_texture, NULL, NULL, &this->_textureWidth, &this->_textureHeight);
}

TextureObject::~TextureObject()
{
	if(this->_texture != nullptr)
	{
		SDL_DestroyTexture(this->_texture);
	}
}

TextureObject::TextureObject(const TextureObject &obj)
{
	_hasTexture = obj._hasTexture;
	_renderer = obj._renderer;
	_pathToFile = obj._pathToFile;
	loadTexture(_pathToFile);
	_textureWidth = obj._textureWidth;
	_textureHeight = obj._textureHeight;
}

TextureObject& TextureObject::operator=(const TextureObject& obj)
{
	_hasTexture = obj._hasTexture;
	_renderer = obj._renderer;
	_pathToFile = obj._pathToFile;
	loadTexture(_pathToFile);
	_textureWidth = obj._textureWidth;
	_textureHeight = obj._textureHeight;
}	

void TextureObject::render()
{
	if(this->_hasTexture)
	{
		SDL_RenderCopy(this->_renderer, this->_texture, NULL, NULL);
	}
}

void TextureObject::render(SDL_Rect *clipPositionOnScreen)
{
	if(this->_hasTexture)
	{
		SDL_RenderCopy(this->_renderer, this->_texture, NULL, clipPositionOnScreen);
	}
}

void TextureObject::render(SDL_Rect *clipPositionOnScreen, SDL_Rect *clipPositionOnTexture)
{
	if(this->_hasTexture)
	{
		SDL_RenderCopy(this->_renderer, this->_texture, clipPositionOnTexture, clipPositionOnScreen);
	}
}

bool TextureObject::loadTexture(const std::string &pathToFile, SDL_Renderer* rendererObject)
{
	this->_renderer = rendererObject;
	this->loadTexture(pathToFile);
}

bool TextureObject::loadTexture(const std::string &pathToFile)
{
	//~ std::cout<<"Path to File = "<<pathToFile<<std::endl;
	if(this->_hasTexture)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture = IMG_LoadTexture(this->_renderer, pathToFile.c_str());
		if (this->_texture == nullptr)
		{
			this->_hasTexture = false;
			std::cout<<"LoadTexture error"<<std::endl;
		}
		else
		{
			this->_hasTexture = true;
		}
	}
	else
	{
		this->_texture = IMG_LoadTexture(this->_renderer, pathToFile.c_str());
		if (this->_texture == nullptr)
		{
			std::cout<<"LoadTexture error"<<std::endl;
		}
		else
		{
			_hasTexture = true;
		}
	}
}

int TextureObject::getTextureWidth()
{
	return this->_textureWidth;
}
		
int TextureObject::getTextureHeight()
{
	return this->_textureHeight;
}
