#include<MultiSprite.hpp>

MultiSprite::MultiSprite()
: Sprite(), _activeClipNumber(0), _clipArray(), _clipArraySize(0)
{
	
}

MultiSprite::MultiSprite(std::string pathToFile, SDL_Renderer* rendererData, ClipArray &clipArrayData)
: Sprite(pathToFile, rendererData), _activeClipNumber(0), _clipArray(clipArrayData), _clipArraySize(0)
{
	this->_clipArraySize = _clipArray.getSize();
}

MultiSprite::MultiSprite(const MultiSprite &obj)
: Sprite(obj)
{
	_clipArray = obj._clipArray;
	_activeClipNumber = obj._activeClipNumber;
	_clipArraySize = obj._clipArraySize;
}

MultiSprite& MultiSprite::operator=(const MultiSprite& obj)
{
	Sprite::operator=(obj);
	_clipArray = obj._clipArray;
	_activeClipNumber = obj._activeClipNumber;
	_clipArraySize = obj._clipArraySize;
}

MultiSprite::~MultiSprite()
{
	
}

void MultiSprite::render()
{
	if(this->_clipArraySize)
	{
		SDL_Rect clipPositionOnScreen;
		clipPositionOnScreen.x = this->getXPosition();
		clipPositionOnScreen.y = this->getYPosition();
		SDL_Rect clipPositionOnTexture = this->_clipArray.getClip(this->_activeClipNumber);
		clipPositionOnScreen.w = clipPositionOnTexture.w;
		clipPositionOnScreen.h = clipPositionOnTexture.h;
		this->getActualTexture()->render(&clipPositionOnScreen, &clipPositionOnTexture);
	}
}

int MultiSprite::getTextureWidth()
{
	SDL_Rect actualClip = this->_clipArray.getClip(this->_activeClipNumber);
	return actualClip.w;
}

int MultiSprite::getTextureHeight()
{
	SDL_Rect actualClip = this->_clipArray.getClip(this->_activeClipNumber);
	return actualClip.h;
}

int MultiSprite::getClipArraySize()
{
	return this->_clipArraySize;
}

void MultiSprite::setClipNumber(int clipNumber)
{
	if((clipNumber >= 0) && (clipNumber < this->_clipArraySize) )
	{
		this->_activeClipNumber = clipNumber;
	}
}
