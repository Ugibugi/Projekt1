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
	/*
	int Padding = 50;
	int RowHeight = 25;
	int ColWidth = 25;*/

	std::array<std::array<utl::uDisplayObject, 11>, 6> invaders;
	utl::uDisplayObject player;
	utl::uDisplayObject laser;
	void load()
	{
		SDL_DisplayMode info;
		SDL_GetCurrentDisplayMode(0, &info);
		auto procentW = [&info](int x)
		{
			std::clamp(x, 0, 100);
			float onePercent = info.w / 100.0f;
			return (int)onePercent * x;
		};
		auto procentH = [&info](int x)
		{
			std::clamp(x, 0, 100);
			float onePercent = info.h / 100.0f;

			return (int)onePercent * x;
		};
		int Padding = 25;
		int RowHeight = procentH(7);
		int ColWidth = procentW(7);
		//display grid of invaders
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
				invaders[i][j].setWH(ColWidth-10, RowHeight-10);
				invaders[i][j].setXY((j+1)*(ColWidth + Padding), (i+1)*(RowHeight + Padding));
				utl::uDisplayManager::loadObject(&invaders[i][j]);
			}
		}
		player.setImage("res/PLAYER.png");
		utl::uDisplayManager::loadObject(&player);
		player.setXY(invaders.front().back().getTarget()->x, invaders.back().back().getTarget()->y + procentH(10));
	}

	/*void setRowHeight(int newVal)
	{
		RowHeight = newVal;
		for (auto&& rows : invaders)
		{
			for (auto&& invs : rows)
				invs.setWH(ColWidth, RowHeight);	
		}
	}
	void setColWidth(int newVal)
	{
		ColWidth = newVal;
		for (auto&& rows : invaders)
		{
			for (auto&& invs : rows)
				invs.setWH(ColWidth, RowHeight);
		}
	}*/
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
	bool quit = false;
	utl::uInputHandler handler;
	utl::uDisplayManager::init(Game_Window, Game_Renderer);
	utl::uDisplayObject test("res/SPACEA1.png");
	//utl::uDisplayManager::loadObject(&test);
	//KeyMapping
	handler.on(SDL_KEYDOWN, SDLK_LEFT, []() {
		game.player.setXY(game.player.getTarget()->x - 10, game.player.getTarget()->y);
		
	});
	handler.on(SDL_KEYDOWN, SDLK_RIGHT, []() {
		game.player.setXY(game.player.getTarget()->x + 10, game.player.getTarget()->y);
	});
	handler.on(SDL_KEYDOWN, SDLK_ESCAPE, [&quit]()
	{
		quit = true;
	});
	game.load();
	SDL_Event e;
	
	while (!quit)
	{
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}	
		}
		//TODO FIX
		handler.processKeyboard();
		utl::uDisplayManager::draw();
		

		
	}
	utl::uDisplayManager::close();
	SDL_Quit();
	return 0;

}