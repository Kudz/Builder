#ifndef CLIP_ARRAY_HPP
#define CLIP_ARRAY_HPP

#include <iostream>
//#include <memory>

#include <SDL.h>

/**
 * ClipArray creates SDL_Rect object for every active part of texture file. 
 * First clip has to start at 0,0
 * 
 *     0___   ___   ___
 *    0|___| |___| |___| ClipHeigth
 *      ___   ___   ___  yOffset
 *     |___| |___| |___|
 *      ___   ___   ___
 *     |___| |___| |___|
 *       C  x
 * 		 l  O
 *       i  f
 *       p  f
 *       W  s
 *       i  e
 *       d  t
 *       t
 *       h 
 * 
 * @param _size Quantity of Image Clips
 * @param _width Width of Image Clip
 * @param _height Height of Image Clip
 */
 
class ClipArray
{
	public:
		ClipArray();
		
		/**
		 * ClipArray Class Constructor
		 * @param clipWidth Width of Image Clip
		 * @param clipHeight Height of Image Clip
		 * @param colAmount Amount of Clips in row
		 * @param clipAmount Quantity of Image Clips
		 */
		ClipArray(int clipWidth, int clipHeight, int colAmount, int clipAmount);
		
		/**
		 * ClipArray Class Constructor
		 * @param clipWidth Width of Image Clip
		 * @param clipHeight Height of Image Clip
		 * @param colAmount Amount of Clips in row
		 * @param clipAmount Quantity of Image Clips
		 * @param xOffset Space between Clips in row
		 * @param yOffset Space between Clips in column
		 */
		ClipArray(int clipWidth, int clipHeight, int colAmount, int clipAmount, int xOffset, int yOffset);
		ClipArray(const ClipArray &obj);
		ClipArray& operator=(const ClipArray& obj);
		~ClipArray();
		int getSize();
		SDL_Rect getClip(int number);
		int getWidth();
		int getHeight();
	private:
		void init(int clipWidth, int clipHeight, int colAmount, int clipAmount, int xOffset, int yOffset);
		SDL_Rect* _clips;
		int _size; // quantity of Image Clips
		int _width; // width of Image Clip
		int _height; // height of Image Clip
};

#endif
