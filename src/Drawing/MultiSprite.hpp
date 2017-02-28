#ifndef MULTI_SPRITE_HPP
#define MULTI_SPRITE_HPP

#include <SDL.h>

#include <Sprite.hpp>
#include <ClipArray.hpp>

/**
* MultiSprite class
*/
class MultiSprite : public Sprite
{
	public:
		MultiSprite();
		MultiSprite(std::string pathToFile, SDL_Renderer *rendererData, ClipArray &clipArrayData);
		MultiSprite(const MultiSprite &obj);
		MultiSprite& operator=(const MultiSprite& obj);
		~MultiSprite();
		void render();
		int getTextureWidth();
		int getTextureHeight();
		int getClipArraySize();
		void setClipNumber(int clipNumber);
	private:
		ClipArray _clipArray;
		int _clipArraySize;
		int _activeClipNumber; // number of active Clip
};

#endif
