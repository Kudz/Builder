#ifndef CLICKABLE_OBJECT_HPP
#define CLICKABLE_OBJECT_HPP

#include <MultiSprite.hpp>

class ClickableObject
{
	public:
		ClickableObject(MultiSprite multiSpriteObject, int defaultClip = 0, int focusedClip = 0, int clickedClip = 0);
		ClickableObject(const ClickableObject &obj);
		ClickableObject& operator=(const ClickableObject& obj);
		~ClickableObject();
		void render(SDL_Event* e);
		void setDefaultClip(int clipNumber);
		void setFocusedClip(int clipNumber);
		void setClickedClip(int clipNumber);
		void setClipsNumbers(int defaultClip, int focusedClip, int clickedClip);
		void moveObjectAlongX(int xOffset);
		void moveObjectAlongY(int yOffset);
		void setObjectXPosition(int xPosition);
		void setObjectYPosition(int yPosition);
		void setObjectPosition(int xPosition, int yPosition);
	private:
		int _defaultClipNumber;
		int _focusedClipNumber;
		int _clickedClipNumber;
		int _clipArraySize;
		bool _mouseLeftButtonPressed;
		MultiSprite _multiSpriteObject;
	
};

#endif
