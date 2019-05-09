#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <array>
#include <q3.h>
#include "uFunctionStorage.h"
#include "uResource.h"
#include "uDisplayManager.h"
#include "uInputHandler.h"
#include "uDisplayObject.h"
#include "Game.h"
#include "uRendererSDL.h"
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg.c_str() << " error: " << SDL_GetError() << std::endl;
}

int main(int argc, char* argv[])
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	//TTF_Init();
	SDL_Window* Game_Window = SDL_CreateWindow("BLANK", 0,0, 1000,1000, SDL_WINDOW_SHOWN);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	if (Game_Window == nullptr)
	{
		logSDLError(std::cout, "Window");
	}
	//get Display info
	
	utl::uRendererSDL Game_Renderer(Game_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!Game_Renderer.valid)
	{
		logSDLError(std::cout, "SDL_Window");
		SDL_DestroyWindow(Game_Window);
	}

	
	utl::uDisplayManager::init(&Game_Renderer);
	uint32_t Id = SDL_RegisterEvents(1);
	assert(Id == SDL_USEREVENT);
	Game game(Game_Window);
	game.load();
	while (!game.quit)
	{

		game.tick();
		utl::uDisplayManager::draw();
		//std::cout << "x: " << game.laser.getTarget()->x << " y: " << game.laser.getTarget()->y << " wh: " << game.laser.getTarget()->w << " " << game.laser.getTarget()->h << "\n";

	}
	utl::uDisplayManager::close();
	SDL_Quit();
	return 0;

}