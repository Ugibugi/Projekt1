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
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg.c_str() << " error: " << SDL_GetError() << std::endl;
}
struct
{
	const int Padding = 10;
	const int RowHeight = 50;
	const int ColWidth = 50;
	std::array<std::array<utl::uDisplayObject, 11>, 6> invaders;
	utl::uDisplayObject player;
	utl::uDisplayObject laser;
	void load()
	{
		for (size_t i = 0; i < invaders.size(); i++)
		{
			for (size_t j = 0; j < invaders[i].size(); j++)
			{
				switch (i)
				{
				case 0:
				case 1:
					invaders[i][j].setImage("res/SPACEC1.png");
					break;
				case 2:
				case 3:
					invaders[i][j].setImage("res/SPACEB1.png");
					break;
				case 4:
				case 5:
					invaders[i][j].setImage("res/SPACEA1.png");
					break;
				}
				invaders[i][j].setWH(ColWidth, RowHeight);
				invaders[i][j].setXY((j+1)*(ColWidth + Padding), (i+1)*(RowHeight + Padding));
				utl::uDisplayManager::loadObject(&invaders[i][j]);
			}
		}
		
	}
} game;
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
	SDL_Window* Game_Window = SDL_CreateWindow("BLANK", 100,100, 1280, 1024, SDL_WINDOW_SHOWN);
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
	
	

	utl::uInputHandler handler;
	utl::uDisplayManager::init(Game_Window, Game_Renderer);
	utl::uDisplayObject test("res/SPACEA1.png");
	utl::uDisplayManager::loadObject(&test);
	int w=100, h=100;
	test.setWH(w, h);
	//TODO Fix .set("")function
	//KeyMapping
	handler.on(SDL_KEYDOWN, SDLK_DOWN, [&test]() {
		test.setImage("res/SPACEA1.png");
		
	});
	handler.on(SDL_KEYDOWN, SDLK_UP, [&test]() {
		test.setImage("res/SPACEA2.png");
		
	});
	handler.on(SDL_KEYDOWN, SDLK_LEFT, [&test,&w,&h]() {
		w += 10;
		h += 10;
		test.setWH(w, h);
		
	});
	handler.on(SDL_KEYDOWN, SDLK_RIGHT, [&test, &w, &h]() {
		w -= 10;
		h -= 10;
		test.setWH(w, h);
	});

	//game.load();
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
				handler.newEvent(e.type, e.key.keysym.sym);
			}
		}

		utl::uDisplayManager::draw();
		

		
	}
	utl::uDisplayManager::close();
	SDL_Quit();
	return 0;

}