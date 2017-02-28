#include <ClipArray.hpp>

ClipArray::ClipArray()
:_clips(NULL), _size(0), _width(0), _height(0)
{

}

ClipArray::ClipArray(int clipWidth, int clipHeight, int colAmount, int clipAmount)
:_clips(NULL), _size(0), _width(0), _height(0)
{
	this->init(clipWidth, clipHeight, colAmount, clipAmount, clipWidth, clipHeight);
}

ClipArray::ClipArray(int clipWidth, int clipHeight, int colAmount, int clipAmount, int xOffset, int yOffset)
:_clips(NULL), _size(0), _width(0), _height(0)
{
	this->init(clipWidth, clipHeight, colAmount, clipAmount, xOffset, yOffset);
}

void ClipArray::init(int clipWidth, int clipHeight, int colAmount, int clipAmount, int xOffset, int yOffset)
{	
	this->_size = clipAmount;
	if(this->_clips == nullptr)
	{
		this->_clips = new SDL_Rect[this->_size];
		for(int i=0; i<this->_size; i++)
		{
			this->_clips[i].x = (i % colAmount) * (clipWidth + xOffset);
			this->_clips[i].y = (i / colAmount) * (clipHeight + yOffset);
			this->_clips[i].w = clipWidth;
			this->_clips[i].h = clipHeight;
		}
	}
}

ClipArray::ClipArray( const ClipArray &obj)
{
	_size = obj._size;
	_width = obj._width;
	_height = obj._height;
	_clips = new SDL_Rect[obj._size];
	for(int i = 0; i < obj._size; i++)
	{
		_clips[i] = obj._clips[i];
	}
}

ClipArray& ClipArray::operator=(const ClipArray& obj)
{
	_size = obj._size;
	_width = obj._width;
	_height = obj._height;
	_clips = new SDL_Rect[obj._size];
	for(int i = 0; i < obj._size; i++)
	{
		_clips[i] = obj._clips[i];
	}
}

int ClipArray::getSize()
{
	return this->_size;
}

SDL_Rect ClipArray::getClip(int number)
{
	return this->_clips[number];
}

ClipArray::~ClipArray()
{
	if(this->_clips != nullptr)
	{
		delete[] this->_clips;
	}
}

int ClipArray::getWidth()
{
	return this->_width;
}

int ClipArray::getHeight()
{
	return this->_height;
}

