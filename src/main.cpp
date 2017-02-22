#include <iostream>

//#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <cleanup.hpp>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

int main(int argc, char *argv[])
{

	std::cout<<"begining"<<std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout<<"SDL_Init error"<<std::endl;
		return 1;
	}

	std::cout<<"window"<<std::endl;
	SDL_Window *window = SDL_CreateWindow("Shop builder", 100, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout<<"CreateWindow error"<<std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout<<"CreateRenderer error"<<std::endl;
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	//Our event structure
	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT)
				quit = true;
			//Use number input to select which clip should be drawn
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
			SDL_RenderPresent(renderer);
		}
	}

	std::cout<<"before cleaning"<<std::endl;

	cleanup(renderer, window);
	SDL_Quit();

	std::cout<<"end of program"<<std::endl;

	return 0;
}
