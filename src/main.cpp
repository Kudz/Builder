//#include <iostream>
#include <algorithm> // std::replace

//#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include <TextureObject.hpp>
#include <Sprite.hpp>
#include <MultiSprite.hpp>
#include <ClickableObject.hpp>

#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;

int main(int argc, char *argv[])
{

	std::cout<<"begining"<<std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout<<"SDL_Init error"<<std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cout<<"IMG_INT error"<<std::endl;
		SDL_Quit();
		return 1;
	}

	std::cout<<"window"<<std::endl;
	SDL_Window *window = SDL_CreateWindow("Builder", 100, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // SDL_WINDOW_SHOWN is ignored
	if (window == nullptr)
	{
		std::cout<<"CreateWindow error"<<std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_SetWindowBrightness(window, 1.0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout<<"CreateRenderer renderer2 error"<<std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Select the white color for cleaning the window
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	std::string pngDirectoryPath = SOURCEFOLDERPATH;
	std::replace( pngDirectoryPath.begin(), pngDirectoryPath.end(), '/', '\\');
	pngDirectoryPath = pngDirectoryPath + PATH_SEP;
	pngDirectoryPath = pngDirectoryPath + "graphics";
	pngDirectoryPath = pngDirectoryPath + PATH_SEP;
	pngDirectoryPath = pngDirectoryPath + "png";
	pngDirectoryPath = pngDirectoryPath + PATH_SEP;
	std::string backgroundPNG = pngDirectoryPath + "TitleScreen.png";
	std::string buttonsPNG = pngDirectoryPath + "Button.png";
	std::string kwadratyPNG = pngDirectoryPath + "kwadraty.png";
	
	std::cout<<"twoButton path = "<<buttonsPNG<<std::endl;
	TextureObject backgroundTexture(backgroundPNG, renderer);
	
	//~ TextureObject emptyTexture(kwadratyPNG, renderer);
	TextureObject emptyTexture;
	MultiSprite emptyMultiSprite;
	emptyTexture.loadTexture(kwadratyPNG);
	
	Sprite twoButton(buttonsPNG, renderer);
	twoButton.setPosition(100,100);
	
	ClipArray buttonClipArray(400, 100, 1, 3, 0, 20);
	MultiSprite buttonMultiSprite(buttonsPNG, renderer, buttonClipArray);
	buttonMultiSprite.setPosition((SCREEN_WIDTH/2) - (buttonMultiSprite.getTextureWidth()/2),150);
	
	ClickableObject firstButton(buttonMultiSprite, 0, 1, 2);
	
	std::cout<<"before second Button"<<std::endl;
	ClickableObject secondButton = firstButton;
	secondButton.moveObjectAlongY(150);
	
	std::cout<<"before third Button"<<std::endl;
	ClickableObject thirdButton(secondButton);
	thirdButton.moveObjectAlongY(150);
	
	ClipArray kwadratyClipArray(64, 64, 3, 10, 32, 32);
	MultiSprite kwadraty(kwadratyPNG, renderer, kwadratyClipArray);
	kwadraty.setPosition((SCREEN_WIDTH/2) - (kwadraty.getTextureWidth()/2),450);

	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}
			}
			SDL_RenderClear(renderer);
			backgroundTexture.render();
		//	twoButton.render();
			//~ buttonMultiSprite.render(&e);
			firstButton.render(&e);
			secondButton.render(&e);
			thirdButton.render(&e);
			//~ kwadraty.render(&e);
			emptyTexture.render();
			emptyMultiSprite.render();
			SDL_RenderPresent(renderer);
		}
	}

	std::cout<<"before cleaning"<<std::endl;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	std::cout<<"end of program"<<std::endl;

	return 0;
}
