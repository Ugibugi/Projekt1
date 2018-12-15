#pragma once
#include <array>

#include "uFunctionStorage.h"
#include "uResource.h"
#include "uDisplayManager.h"
#include "uInputHandler.h"
#include "uDisplayObject.h"
#include "uRendererSDL.h"
#include "uPhysicsObject.h"
#include "uGameObject.h"
/*
temporary Game class for testing purposes.

*/
class Game
{
public:
	typedef utl::uGameObject<utl::uPhysicsObject, utl::uSDLRenderObject> GameObject;
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
				invaders[i][j].DT::setWH(ColWidth - 10, RowHeight - 5);
				invaders[i][j].DT::setXY((j)*(ColWidth + Padding), (i + 1)*(RowHeight + Padding));
				utl::uDisplayManager::loadObject(&invaders[i][j]);
			}
		}

		//Initialise other display objects
		player.setImage("res/PLAYER.png");
		player.DT::setWH(ColWidth, RowHeight);
		utl::uDisplayManager::loadObject(&player);
		player.DT::setXY(invaders.front().back().DT::getTarget()->x, invaders.back().back().DT::getTarget()->y + procentH(25));

		laser.setImage("res/LASER.png");
		laser.setDefaultWH();
		laser.DT::setXY(&player);
		laser.DT::active = false;
		utl::uDisplayManager::loadObject(&laser);

		//define keymappings
		handler.on(SDL_KEYDOWN, SDLK_LEFT, [this]() {
			player.DT::setXY(player.DT::getTarget()->x - 10, player.DT::getTarget()->y);
			if (player.DT::getTarget()->x < 0) player.DT::setXY(0, player.DT::getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_RIGHT, [this]() {
			player.DT::setXY(player.DT::getTarget()->x + 10, player.DT::getTarget()->y);
			if (player.DT::getTarget()->x + player.DT::getTarget()->w > displayInfo.w) player.DT::setXY(displayInfo.w - player.DT::getTarget()->w, player.DT::getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_ESCAPE, [this]() {
			quit = true;
		});

		handler.on(SDL_KEYDOWN, SDLK_SPACE, [this]() {
			if (!shootActive)
			{
				laser.DT::setXY(player.DT::getTarget()->x + player.DT::getTarget()->w/2,player.DT::getTarget()->y);
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
		laser.DT::active = true;
		if (laser.DT::getTarget()->y <= 0)
		{
			laser.DT::active = false;
			shootActive = false;
		}
		laser.DT::setXY(laser.DT::getTarget()->x, laser.DT::getTarget()->y - 10);
	}

	inline int procentW(int x)
	{
		int xx = std::clamp(x, 0, 100);
		float onePercent = displayInfo.w / 100.0f;
		return (int)onePercent * xx;
	};
	inline int procentH(int x)
	{
		int xx = std::clamp(x, 0, 100);
		float onePercent = displayInfo.h / 100.0f;
		return (int)onePercent * xx;
	};

	std::array<std::array<GameObject, 12>, 6> invaders;
	GameObject player;
	GameObject laser;
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