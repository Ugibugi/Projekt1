#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include "uFunctionStorage.h"
#include "uResource.h"
#include "uDisplayManager.h"
#include <tuple>
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
	SDL_Window* Game_Window = SDL_CreateWindow("BLANK", 100,100, 800, 600, SDL_WINDOW_SHOWN);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	if (Game_Window == nullptr)
	{
		logSDLError(std::cout, "Window");
	}
	SDL_Renderer* Game_Renderer = SDL_CreateRenderer(Game_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Game_Renderer == nullptr)
	{
		logSDLError(std::cout, "SDL_Window");
		SDL_DestroyWindow(Game_Window);
	}
#pragma endregion
	utl::uFunctionStorage test_storage;
	uint32_t TEST_FUNC = 1;

	
	int i = 2, j = 4;
	test_storage.addCall(TEST_FUNC, std::printf, "i = %d \n j = %d", i, j);
	test_storage.Call(TEST_FUNC);
	

	utl::uDisplayManager::init(Game_Window, Game_Renderer);

	utl::uDisplayObject test;
	test.srcImage.set("420.jpg");
	test.setXY(100, 100);

	utl::uDisplayManager::loadObject(&test);
	

	SDL_Event e;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_DOWN:
					break;
				default:
					//TODO
					break;
				}
			}
		}

		utl::uDisplayManager::draw();
		

		
	}
	utl::uDisplayManager::close();
	SDL_Quit();
	return 0;

}