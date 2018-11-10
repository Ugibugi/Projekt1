#pragma once
#include <array>

#include "uFunctionStorage.h"
#include "uResource.h"
#include "uDisplayManager.h"
#include "uInputHandler.h"
#include "uDisplayObject.h"
#include "uRendererSDL.h"
/*
temporary Game class for testing purposes.

*/
class Game
{
public:

	Game(SDL_Window* window)
	{
		//Get viewport dismensions
		SDL_GetWindowSize(window, &displayInfo.w,&displayInfo.h);
	}
	
	void load()
	{
		
		int Padding = procentW(1);
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
				invaders[i][j].setWH(ColWidth - 10, RowHeight - 5);
				invaders[i][j].setXY((j)*(ColWidth + Padding), (i + 1)*(RowHeight + Padding));
				utl::uDisplayManager::loadObject(&invaders[i][j]);
			}
		}

		//Initialise other display objects
		player.setImage("res/PLAYER.png");
		player.setWH(ColWidth, RowHeight);
		utl::uDisplayManager::loadObject(&player);
		player.setXY(invaders.front().back().getTarget()->x, invaders.back().back().getTarget()->y + procentH(25));

		laser.setImage("res/LASER.png");
		laser.setDefaultWH();
		laser.setXY(&player);
		laser.active = false;
		utl::uDisplayManager::loadObject(&laser);

		//define keymappings
		handler.on(SDL_KEYDOWN, SDLK_LEFT, [this]() {
			player.setXY(player.getTarget()->x - 10, player.getTarget()->y);
			if (player.getTarget()->x < 0) player.setXY(0, player.getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_RIGHT, [this]() {
			player.setXY(player.getTarget()->x + 10, player.getTarget()->y);
			if (player.getTarget()->x + player.getTarget()->w > displayInfo.w) player.setXY(displayInfo.w - player.getTarget()->w, player.getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_ESCAPE, [this]() {
			quit = true;
		});

		handler.on(SDL_KEYDOWN, SDLK_SPACE, [this]() {
			if (!shootActive)
			{
				laser.setXY(player.getTarget()->x + player.getTarget()->w/2,player.getTarget()->y);
				shootActive = true;
			}
		});


	}

	void tick()
	{
		if (!pause)
		{
			if (shootActive)
				shoot();
		}
		handler.processKeyboard();
	}
	void shoot()
	{
		laser.active = true;
		if (laser.getTarget()->y <= 0)
		{
			laser.active = false;
			shootActive = false;
		}
		laser.setXY(laser.getTarget()->x, laser.getTarget()->y - 10);
	}

	inline int procentW(int x)
	{
		std::clamp(x, 0, 100);
		float onePercent = displayInfo.w / 100.0f;
		return (int)onePercent * x;
	};
	inline int procentH(int x)
	{
		std::clamp(x, 0, 100);
		float onePercent = displayInfo.h / 100.0f;
		return (int)onePercent * x;
	};

	std::array<std::array<utl::uSDLRenderObject, 12>, 6> invaders;
	utl::uSDLRenderObject player;
	utl::uSDLRenderObject laser;
	bool quit = false;
	utl::uInputHandler handler;
	SDL_DisplayMode displayInfo;
	bool shootActive = false;
	bool pause= false;
	

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
};