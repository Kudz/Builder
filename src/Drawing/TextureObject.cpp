#include <TextureObject.hpp>

TextureObject::TextureObject()
: _hasTexture(false), _texture(nullptr), _renderer(nullptr)
{
	
}

TextureObject::TextureObject(const std::string &pathToFile, SDL_Renderer* rendererObject)
: _hasTexture(false), _texture(nullptr), _renderer(nullptr)
{
	this->loadTexture(pathToFile, rendererObject);
}

TextureObject::~TextureObject()
{
	if(this->_texture != nullptr)
	{
		SDL_DestroyTexture(this->_texture);
	}
}

void TextureObject::render()
{
	if(this->_hasTexture)
	{
		SDL_RenderCopy(this->_renderer, this->_texture, NULL, NULL);
	}
}


bool TextureObject::loadTexture(const std::string &pathToFile, SDL_Renderer* rendererObject)
{
	this->_renderer = rendererObject;
	this->loadTexture(pathToFile);
}

bool TextureObject::loadTexture(const std::string &pathToFile)
{
	if(this->_hasTexture)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture = IMG_LoadTexture(this->_renderer, pathToFile.c_str());
		if (this->_texture == nullptr)
		{
			this->_hasTexture = false;
			std::cout<<"LoadTexture error"<<std::endl;
			//	std::cout<<"Path to File = "<<pathToFile<<std::endl;
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
			//	std::cout<<"Path to File = "<<pathToFile<<std::endl;
		}
		else
		{
			_hasTexture = true;
		}
	}
}
