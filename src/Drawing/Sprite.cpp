#include<Sprite.hpp>

Sprite::Sprite()
: _xPositionOnScreen(0), _yPositionOnScreen(0), _actualTexture()
{
	
}

Sprite::Sprite(std::string pathToFile, SDL_Renderer *rendererData)
: _xPositionOnScreen(0), _yPositionOnScreen(0), _actualTexture(pathToFile, rendererData)
{

}

Sprite::Sprite(const Sprite &obj)
{
	_actualTexture = obj._actualTexture;
	_xPositionOnScreen = obj._xPositionOnScreen;
	_yPositionOnScreen = obj._yPositionOnScreen;
}

Sprite& Sprite::operator=(const Sprite& obj)
{
	_actualTexture = obj._actualTexture;
	_xPositionOnScreen = obj._xPositionOnScreen;
	_yPositionOnScreen = obj._yPositionOnScreen;
}

Sprite::~Sprite()
{
	
}

void Sprite::render(int newXPosition, int newYPosition)
{
	this->_xPositionOnScreen = newXPosition;
	this->_yPositionOnScreen = newYPosition;
	this->render();
}

void Sprite::render()
{
	SDL_Rect clipPositionOnScreen;
	clipPositionOnScreen.x = this->_xPositionOnScreen;
	clipPositionOnScreen.y = this->_yPositionOnScreen;
	clipPositionOnScreen.w = this->_actualTexture.getTextureWidth();
	clipPositionOnScreen.h = this->_actualTexture.getTextureHeight();
	this->_actualTexture.render(&clipPositionOnScreen);
}

void Sprite::setPosition(int newXPosition, int newYPosition)
{
	this->_xPositionOnScreen = newXPosition;
	this->_yPositionOnScreen = newYPosition;
}

void Sprite::setXPosition(int newXPosition)
{
	this->_xPositionOnScreen = newXPosition;
}

void Sprite::setYPosition(int newYPosition)
{
	this->_yPositionOnScreen = newYPosition;
}

int Sprite::getXPosition()
{
	return this->_xPositionOnScreen;
}

int Sprite::getYPosition()
{
	return this->_yPositionOnScreen;
}

int Sprite::getTextureWidth()
{
	return this->_actualTexture.getTextureWidth();
}

int Sprite::getTextureHeight()
{
	return this->_actualTexture.getTextureHeight();
}

TextureObject* Sprite::getActualTexture()
{
	return &this->_actualTexture;
}
