#pragma once
#include <array>
#include "Utils.h"
#include "uFunctionStorage.h"
#include "uResource.h"
#include "uDisplayManager.h"
#include "uInputHandler.h"
#include "uDisplayObject.h"
#include "uRendererSDL.h"
#include "uPhysicsObject.h"
#include "uGameObject.h"
#include "uPhysicsManager.h"
#include "uTimer.h"
/*
temporary Game class for testing purposes.

*/
class Game
{
	enum
	{
		INVADER_CLASS,
		PLAYER_CLASS,
		LASER_CLASS,
		MISSLE_CLASS
	};
	typedef utl::uGameObject<utl::uPhysicsObject, utl::uSDLRenderObject> GameObject;
	class GameInvader : public GameObject
	{
	public:
		GameInvader()
		{
			GameObject::PT::_groupId = INVADER_CLASS;
		}
		enum
		{
			A, B, C
		}type;
		bool dying;
	};
	class GamePlayer : public GameObject
	{
	public:
		GamePlayer()
		{
			GameObject::PT::_groupId = PLAYER_CLASS;
		}
	};
	class GameLaser : public GameObject
	{
	public:
		GameLaser()
		{
			GameObject::PT::_groupId = LASER_CLASS;
		}
	};

public:

	Game(SDL_Window* window) : timer60ps(17) //17ms ~~ 60 Hz
	{
		//Get viewport dismensions
		SDL_GetWindowSize(window, &displayInfo.w, &displayInfo.h);
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
				physicsManager.addObject(&invaders[i][j]);
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
		handler.on(SDL_KEYDOWN, SDLK_LEFT, [this](SDL_Event* e) {
			player.DT::setXY(player.DT::getTarget()->x - 10, player.DT::getTarget()->y);
			if (player.DT::getTarget()->x < 0) player.DT::setXY(0, player.DT::getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_RIGHT, [this](SDL_Event* e) {
			player.DT::setXY(player.DT::getTarget()->x + 10, player.DT::getTarget()->y);
			if (player.DT::getTarget()->x + player.DT::getTarget()->w > displayInfo.w) player.DT::setXY(displayInfo.w - player.DT::getTarget()->w, player.DT::getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_ESCAPE, [this](SDL_Event* e) {
			quit = true;
		});

		handler.on(SDL_KEYDOWN, SDLK_SPACE, [this](SDL_Event* e) {
			if (!shootActive)
			{
				laser.DT::setXY(player.DT::getTarget()->x + player.DT::getTarget()->w / 2, player.DT::getTarget()->y);
				shootActive = true;
			}
		});
		handler.on(SDL_QUIT, NULL, [this](SDL_Event* e) {
			quit = true;
		});
		/*handler.on(SDL_MOUSEMOTION, NULL, [this](SDL_Event* e) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			player.PT::getTarget()->x = x;
		});*/
		handler.on(SDL_USEREVENT, NULL, [this](SDL_Event* e) {

			auto* obj1 = (GameObject*)e->user.data1;
			auto* obj2 = (GameObject*)e->user.data2;

			if (obj1->_groupId == LASER_CLASS || obj2->_groupId == LASER_CLASS)
			{
				if (obj1->_groupId == INVADER_CLASS) killInvader(obj1);
				else if (obj2->_groupId == INVADER_CLASS)killInvader(obj2);
			}

			//std::cout << "HIT REGISTERED\n";
		});
		/*physicsManager.Handler().addCall<GameInvader, GameLaser>(INVADER_CLASS, LASER_CLASS, [this](GameInvader* inv, GameLaser* las) {

			std::cout << "HIT REGISTERED\n";

		});*/
		timer60ps.addCall(1, [this]() { physicsManager.Update(17); });



	}
	void killInvader(GameObject* obj)
	{

	}
	void tick()
	{
		if (!pause)
		{
			if (shootActive)
				shoot();
		}
		handler.processEvents();
		timer60ps.updateTimer();
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

	std::array<std::array<GameInvader, 12>, 6> invaders;
	GamePlayer player;
	GameLaser laser;
	bool quit = false;
	utl::uInputHandler handler;
	utl::uPhysicsManager physicsManager;
	utl::uSynchronisedTimer timer60ps;
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