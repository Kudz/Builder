#include <GameManager.hpp>

GameManager::GameManager()
: _screenWidth(800), _screenHeight(600), _SDLInitialisation(false), _pathToSourceFolder(""), _window(nullptr), _renderer(nullptr)
{
	this->initializeSDL();
	this->_pathToSourceFolder = SOURCEFOLDERPATH;
	std::cout<<"sourcePath = "<<this->_pathToSourceFolder<<std::endl;
	std::replace( this->_pathToSourceFolder.begin(), this->_pathToSourceFolder.end(), '/', '\\');
}

void GameManager::initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout<<"SDL_Init error"<<std::endl;
		return;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cout<<"IMG_INT error"<<std::endl;
		SDL_Quit();
		return;
	}
	
	if (TTF_Init() != 0){
		std::cout<<"TTF_Init error"<<std::endl;
		IMG_Quit();
		SDL_Quit();
		return;
	}
	
	this->_window = SDL_CreateWindow("Builder", 100, 100, this->_screenWidth,
		this->_screenHeight, SDL_WINDOW_SHOWN); // SDL_WINDOW_SHOWN is ignored
	if (this->_window == nullptr)
	{
		std::cout<<"CreateWindow error"<<std::endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return;
	}

	this->_renderer = SDL_CreateRenderer(this->_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->_renderer == nullptr)
	{
		std::cout<<"CreateRenderer error"<<std::endl;
		SDL_DestroyWindow(this->_window);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return;
	}
	
	// Selecting the white color for cleaning the window
	SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
	
	_SDLInitialisation = true;
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);
	atexit(TTF_Quit); // Ensure TTF_Quit() is called when we exit
	atexit(IMG_Quit); // Ensure TTF_Quit() is called when we exit
	atexit(SDL_Quit); // Ensure TTF_Quit() is called when we exit
}

void GameManager::run()
{
	if(_SDLInitialisation)
	{
		std::string pngDirectoryPath = SOURCEFOLDERPATH;
		//~ std::replace( pngDirectoryPath.begin(), pngDirectoryPath.end(), '/', '\\');
		//~ pngDirectoryPath = pngDirectoryPath + PATH_SEP;
		//~ pngDirectoryPath = pngDirectoryPath + "graphics";
		//~ pngDirectoryPath = pngDirectoryPath + PATH_SEP;
		//~ pngDirectoryPath = pngDirectoryPath + "png";
		//~ pngDirectoryPath = pngDirectoryPath + PATH_SEP;
		pngDirectoryPath = pngDirectoryPath + "/graphics/png/";
		CSF::adjustPath(pngDirectoryPath);
		std::string backgroundPNG = pngDirectoryPath + "TitleScreen.png";
		std::string buttonsPNG = pngDirectoryPath + "Button.png";

		std::string fontSansDirectoryPath = SOURCEFOLDERPATH;
		//~ std::replace( fontSansDirectoryPath.begin(), fontSansDirectoryPath.end(), '/', '\\');
		//~ fontSansDirectoryPath = fontSansDirectoryPath + PATH_SEP;
		//~ fontSansDirectoryPath = fontSansDirectoryPath + "fonts";
		//~ fontSansDirectoryPath = fontSansDirectoryPath + PATH_SEP;
		//~ fontSansDirectoryPath = fontSansDirectoryPath + "open_sans";
		//~ fontSansDirectoryPath = fontSansDirectoryPath + PATH_SEP;
		fontSansDirectoryPath = fontSansDirectoryPath + "/fonts/open_sans/";
		CSF::adjustPath(fontSansDirectoryPath);
		std::string openSansFONT = fontSansDirectoryPath + "OpenSans-Regular.ttf";

		TextObject messageTexture(openSansFONT, this->_renderer, "Builder v0.1");
		messageTexture.setPositionOnScreen(this->_screenWidth - messageTexture.getTextureWidth(), this->_screenHeight - messageTexture.getTextureHeight());

		TextureObject backgroundTexture(backgroundPNG, this->_renderer);

		ClipArray buttonClipArray(400, 100, 1, 3, 0, 20);
		MultiSprite buttonMultiSprite(buttonsPNG, this->_renderer, buttonClipArray);
		buttonMultiSprite.setPosition((this->_screenWidth/2) - (buttonMultiSprite.getTextureWidth()/2),150);

		ClickableObject firstButton(buttonMultiSprite, 0, 1, 2);

		TextObject newGameMessageTexture(openSansFONT, this->_renderer, "New Game", 32);
		newGameMessageTexture.setPositionOnScreen(firstButton.getObjectXPosition() + ((firstButton.getObjectTextureWidth()-newGameMessageTexture.getTextureWidth())/2), firstButton.getObjectYPosition() + ((firstButton.getObjectTextureHeight()-newGameMessageTexture.getTextureHeight())/2));

		ClickableObject secondButton = firstButton;
		secondButton.moveObjectAlongY(150);

		TextObject loadGameMessageTexture(openSansFONT, this->_renderer, "Load Game", 32);
		loadGameMessageTexture.setPositionOnScreen(secondButton.getObjectXPosition() + ((secondButton.getObjectTextureWidth()-loadGameMessageTexture.getTextureWidth())/2), secondButton.getObjectYPosition() + ((secondButton.getObjectTextureHeight()-loadGameMessageTexture.getTextureHeight())/2));

		ClickableObject thirdButton(secondButton);
		thirdButton.moveObjectAlongY(150);

		TextObject exitGameMessageTexture(openSansFONT, this->_renderer, "Exit", 32);
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
				SDL_RenderClear(this->_renderer);
				backgroundTexture.render();
				firstButton.render(&e);
				newGameMessageTexture.render();
				secondButton.render(&e);
				loadGameMessageTexture.render();
				thirdButton.render(&e);
				exitGameMessageTexture.render();
				messageTexture.render();
				SDL_RenderPresent(this->_renderer);
			}
		}
	}
}
