#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>
#include <cmath>

#include "uFunctionStorage.h"
#include "uResource.h"
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

	/*utl::uFunctionStorage test_storage;
	uint32_t TEST_FUNC = 1;

	test_storage.addCall<int, double>(TEST_FUNC,test,4, 5.1);
	test_storage.Call(TEST_FUNC);*/

	//TODO fix custom types
	utl::uResource<SDL_Surface, utl::uResourceManager::loadImage, SDL_FreeSurface>::Handle image;
	image.set("420.jpg");
	image.get();
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
					//TODO
					break;
				default:
					//TODO
					break;
				}
			}
		}
		
		SDL_Rect rect[] = { {(int)std::floor(100 * std::sin(SDL_GetTicks())),(int)std::floor(100 * std::cos(SDL_GetTicks())),100,100},
		{ (int)std::floor(100 * std::sin(SDL_GetTicks())) + 100,(int)std::floor(100 * std::cos(SDL_GetTicks())) + 100,100,100 },
		{ (int)std::floor(100 * std::cos(SDL_GetTicks())) + 200,(int)std::floor(100 * std::sin(SDL_GetTicks())) + 200,100,100 } };
		SDL_SetRenderDrawColor(Game_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Game_Renderer);

		SDL_SetRenderDrawColor(Game_Renderer, 0, 0, 0, 0xff);
		SDL_RenderFillRects(Game_Renderer, rect,3);
		SDL_RenderPresent(Game_Renderer);
	}
	SDL_Quit();
	return 0;

}