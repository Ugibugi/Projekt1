#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <array>
#include "uFunctionStorage.h"
#include "uResource.h"
#include "uDisplayManager.h"
#include "uInputHandler.h"
#include "uDisplayObject.h"
#include "Game.h"
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg.c_str() << " error: " << SDL_GetError() << std::endl;
}

int main(int argc, char* argv[])
{
#pragma region Initialization

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	//TTF_Init();
	SDL_Window* Game_Window = SDL_CreateWindow("BLANK", 0,0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	if (Game_Window == nullptr)
	{
		logSDLError(std::cout, "Window");
	}
	//get Display info
	
	


	SDL_Renderer* Game_Renderer = SDL_CreateRenderer(Game_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Game_Renderer == nullptr)
	{
		logSDLError(std::cout, "SDL_Window");
		SDL_DestroyWindow(Game_Window);
	}
#pragma endregion
	
	utl::uDisplayManager::init(Game_Window, Game_Renderer);

	Game game;
	game.load();
	SDL_Event e;
	
	while (!game.quit)
	{
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				game.quit = true;
			}	
		}

		game.tick();
		utl::uDisplayManager::draw();

	}
	utl::uDisplayManager::close();
	SDL_Quit();
	return 0;

}