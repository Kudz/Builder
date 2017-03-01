#include <ClickableObject.hpp>

ClickableObject::ClickableObject(MultiSprite multiSpriteObject, int defaultClip, int focusedClip, int clickedClip)
: _multiSpriteObject(multiSpriteObject), _defaultClipNumber(0), _focusedClipNumber(0), _clickedClipNumber(0), _mouseLeftButtonPressed(false)
{
	this->_clipArraySize = this->_multiSpriteObject.getClipArraySize();
	this->setDefaultClip(defaultClip);
	this->setFocusedClip(focusedClip);
	this->setClickedClip(clickedClip);
}

ClickableObject::ClickableObject(const ClickableObject &obj)
{
	//~ std::cout<<"ClickableObject::ClickableObject(const ClickableObject &obj)"<<std::endl;
	_defaultClipNumber = obj._defaultClipNumber;
	_focusedClipNumber = obj._focusedClipNumber;
	_clickedClipNumber = obj._clickedClipNumber;
	_clipArraySize = obj._clipArraySize;
	_mouseLeftButtonPressed = obj._mouseLeftButtonPressed;
	_multiSpriteObject = obj._multiSpriteObject;
}

ClickableObject& ClickableObject::operator=(const ClickableObject& obj)
{
	//~ std::cout<<"ClickableObject& ClickableObject::operator=(const ClickableObject& obj)"<<std::endl;
	_defaultClipNumber = obj._defaultClipNumber;
	_focusedClipNumber = obj._focusedClipNumber;
	_clickedClipNumber = obj._clickedClipNumber;
	_clipArraySize = obj._clipArraySize;
	_mouseLeftButtonPressed = obj._mouseLeftButtonPressed;
	_multiSpriteObject = obj._multiSpriteObject;
}

ClickableObject::~ClickableObject()
{
	
}

void ClickableObject::render(SDL_Event* e)
{
	if(e->type == SDL_MOUSEBUTTONDOWN)
	{
		this->_mouseLeftButtonPressed = true;
	}
		
	if(e->type == SDL_MOUSEBUTTONUP)
	{
		this->_mouseLeftButtonPressed = false;
	}
	
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int xMouse;
		int yMouse;
		SDL_GetMouseState(&xMouse, &yMouse);
		int minX = this->_multiSpriteObject.getXPosition();
		int maxX = minX + this->_multiSpriteObject.getTextureWidth();
		int minY = this->_multiSpriteObject.getYPosition();
		int maxY = minY + this->_multiSpriteObject.getTextureHeight();
		if((xMouse > minX)&&(xMouse < maxX) && (yMouse > minY) && (yMouse < maxY))
		{
			if(this->_mouseLeftButtonPressed)
			{
				this->_multiSpriteObject.setClipNumber(this->_clickedClipNumber);
			}
			else
			{
				this->_multiSpriteObject.setClipNumber(this->_focusedClipNumber);
			}
		}
		else
		{
			this->_multiSpriteObject.setClipNumber(this->_defaultClipNumber);
			this->_mouseLeftButtonPressed = false;
		}
	}
	this->_multiSpriteObject.render();
}

void ClickableObject::setDefaultClip(int clipNumber)
{
	if((clipNumber >= 0) && (clipNumber < this->_clipArraySize) )
	{
		this->_defaultClipNumber = clipNumber;
	}
}

void ClickableObject::setFocusedClip(int clipNumber)
{
	if((clipNumber >= 0) && (clipNumber < this->_clipArraySize) )
	{
		this->_focusedClipNumber = clipNumber;
	}
}

void ClickableObject::setClickedClip(int clipNumber)
{
	if((clipNumber >= 0) && (clipNumber < this->_clipArraySize) )
	{
		this->_clickedClipNumber = clipNumber;
	}
}

void ClickableObject::setClipsNumbers(int defaultClip, int focusedClip, int clickedClip)
{
	this->setDefaultClip(defaultClip);
	this->setFocusedClip(focusedClip);
	this->setClickedClip(clickedClip);
}

int ClickableObject::getObjectXPosition()
{
	return this->_multiSpriteObject.getXPosition();
}

int ClickableObject::getObjectYPosition()
{
	return this->_multiSpriteObject.getYPosition();
}

void ClickableObject::setObjectPosition(int xPosition, int yPosition)
{
	this->_multiSpriteObject.setPosition(xPosition, yPosition);
}
	
void ClickableObject::setObjectXPosition(int xPosition)
{
	this->_multiSpriteObject.setXPosition(xPosition);
}

void ClickableObject::setObjectYPosition(int yPosition)
{
	this->_multiSpriteObject.setYPosition(yPosition);
}

void ClickableObject::moveObjectAlongX(int xOffset)
{
	this->_multiSpriteObject.setXPosition(this->_multiSpriteObject.getXPosition() + xOffset);
}
		
void ClickableObject::moveObjectAlongY(int yOffset)
{
	this->_multiSpriteObject.setYPosition(this->_multiSpriteObject.getYPosition() + yOffset);
}

int ClickableObject::getObjectTextureWidth()
{
	return this->_multiSpriteObject.getTextureWidth();
}
		
int ClickableObject::getObjectTextureHeight()
{
	return this->_multiSpriteObject.getTextureHeight();
}
