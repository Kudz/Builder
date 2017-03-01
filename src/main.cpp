//#include <iostream>
#include <algorithm> // std::replace

//#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include <TextureObject.hpp>
#include <Sprite.hpp>
#include <MultiSprite.hpp>
#include <ClickableObject.hpp>
#include <TextObject.hpp>

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
	
	if (TTF_Init() != 0){
		std::cout<<"TTF_Init error"<<std::endl;
		IMG_Quit();
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
		std::cout<<"CreateRenderer renderer error"<<std::endl;
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
	
	std::string fontSansDirectoryPath = SOURCEFOLDERPATH;
	std::replace( fontSansDirectoryPath.begin(), fontSansDirectoryPath.end(), '/', '\\');
	fontSansDirectoryPath = fontSansDirectoryPath + PATH_SEP;
	fontSansDirectoryPath = fontSansDirectoryPath + "fonts";
	fontSansDirectoryPath = fontSansDirectoryPath + PATH_SEP;
	fontSansDirectoryPath = fontSansDirectoryPath + "open_sans";
	fontSansDirectoryPath = fontSansDirectoryPath + PATH_SEP;
	std::string openSansFONT = fontSansDirectoryPath + "OpenSans-Regular.ttf";
	
	TextObject messageTexture(openSansFONT, renderer, "Builder v0.1");
	messageTexture.setPositionOnScreen(SCREEN_WIDTH - messageTexture.getTextureWidth(), SCREEN_HEIGHT - messageTexture.getTextureHeight());
	
	TextureObject backgroundTexture(backgroundPNG, renderer);
	
	ClipArray buttonClipArray(400, 100, 1, 3, 0, 20);
	MultiSprite buttonMultiSprite(buttonsPNG, renderer, buttonClipArray);
	buttonMultiSprite.setPosition((SCREEN_WIDTH/2) - (buttonMultiSprite.getTextureWidth()/2),150);
	
	ClickableObject firstButton(buttonMultiSprite, 0, 1, 2);
	
	TextObject newGameMessageTexture(openSansFONT, renderer, "New Game", 32);
	newGameMessageTexture.setPositionOnScreen(firstButton.getObjectXPosition() + ((firstButton.getObjectTextureWidth()-newGameMessageTexture.getTextureWidth())/2), firstButton.getObjectYPosition() + ((firstButton.getObjectTextureHeight()-newGameMessageTexture.getTextureHeight())/2));
	
	ClickableObject secondButton = firstButton;
	secondButton.moveObjectAlongY(150);
	
	TextObject loadGameMessageTexture(openSansFONT, renderer, "Load Game", 32);
	loadGameMessageTexture.setPositionOnScreen(secondButton.getObjectXPosition() + ((secondButton.getObjectTextureWidth()-loadGameMessageTexture.getTextureWidth())/2), secondButton.getObjectYPosition() + ((secondButton.getObjectTextureHeight()-loadGameMessageTexture.getTextureHeight())/2));
	
	ClickableObject thirdButton(secondButton);
	thirdButton.moveObjectAlongY(150);
	
	TextObject exitGameMessageTexture(openSansFONT, renderer, "Exit", 32);
	exitGameMessageTexture.setPositionOnScreen(thirdButton.getObjectXPosition() + ((thirdButton.getObjectTextureWidth()-exitGameMessageTexture.getTextureWidth())/2), thirdButton.getObjectYPosition() + ((thirdButton.getObjectTextureHeight()-exitGameMessageTexture.getTextureHeight())/2));

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
			firstButton.render(&e);
			newGameMessageTexture.render();
			secondButton.render(&e);
			loadGameMessageTexture.render();
			thirdButton.render(&e);
			exitGameMessageTexture.render();
			messageTexture.render();
			SDL_RenderPresent(renderer);
		}
	}

	std::cout<<"before cleaning"<<std::endl;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//~ TTF_Quit();
	//~ IMG_Quit();
	//~ SDL_Quit();
	atexit(TTF_Quit); // Ensure TTF_Quit() is called when we exit
	atexit(IMG_Quit); // Ensure TTF_Quit() is called when we exit
	atexit(SDL_Quit); // Ensure TTF_Quit() is called when we exit

	std::cout<<"end of program"<<std::endl;

	return 0;
}
