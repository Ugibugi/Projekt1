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
			GameObject::PT::solid = false;
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
				invaders[i][j].Target().setWH(ColWidth - 10, RowHeight - 5);
				invaders[i][j].Target().setXY((j)*(ColWidth + Padding), (i + 1)*(RowHeight + Padding));
				utl::uDisplayManager::loadObject(&invaders[i][j]);
				physicsManager.addObject(&invaders[i][j]);
			}
		}

		//Initialise other display objects
		player.setImage("res/PLAYER.png");
		player.Target().setWH(ColWidth, RowHeight);
		utl::uDisplayManager::loadObject(&player);
		player.Target().setXY(invaders.front().back().Target().x, invaders.back().back().Target().y + procentH(25));

		laser.setImage("res/LASER.png");
		laser.setDefaultWH();
		laser.DT::setXY(&player);
		laser.DT::active = false;
		utl::uDisplayManager::loadObject(&laser);
		physicsManager.addObject(&laser);

		//define keymappings
		handler.on(SDL_KEYDOWN, SDLK_LEFT, [this](SDL_Event* e) {
			player.Target().setXY(player.Target().x - 10, player.Target().y);
			if (player.Target().x < 0) player.Target().setXY(0, player.Target().y);
		});

		handler.on(SDL_KEYDOWN, SDLK_RIGHT, [this](SDL_Event* e) {
			player.Target().setXY(player.DT::getTarget()->x + 10, player.DT::getTarget()->y);
			if (player.DT::getTarget()->x + player.DT::getTarget()->w > displayInfo.w) player.Target().setXY(displayInfo.w - player.DT::getTarget()->w, player.DT::getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_ESCAPE, [this](SDL_Event* e) {
			quit = true;
		});

		handler.on(SDL_KEYDOWN, SDLK_SPACE, [this](SDL_Event* e) {
			if (!shootActive)
			{
				laser.Target().setXY(player.DT::getTarget()->x + player.DT::getTarget()->w / 2, player.DT::getTarget()->y);
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

			auto* obj1 = (utl::uPhysicsObject*)e->user.data1;
			auto* obj2 = (utl::uPhysicsObject*)e->user.data2;

			if (obj1->_groupId == LASER_CLASS || obj2->_groupId == LASER_CLASS)
			{
				/*if (obj1->_groupId == INVADER_CLASS) killInvader(obj1);
				else if (obj2->_groupId == INVADER_CLASS)killInvader(obj2);*/
			}

			puts("HIT REGISTERED");
		});
		/*physicsManager.Handler().addCall<GameInvader, GameLaser>(INVADER_CLASS, LASER_CLASS, [this](GameInvader* inv, GameLaser* las) {

			std::cout << "HIT REGISTERED\n";

		});*/
		timer60ps.addCall(1, [this]() { physicsManager.Update(17); });



	}
	void killInvader(GameObject* obj)
	{
		obj->setImage("BOOM.png");
		delayTimer.DelayCall(50, [obj]() {
			obj->DT::active = false;
			obj->PT::solid = false;
		});
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
		delayTimer.updateTimer();
	}
	void shoot()
	{
		laser.DT::active = true;
		if (laser.DT::getTarget()->y <= 0)
		{
			laser.DT::active = false;
			shootActive = false;
		}
		laser.Target().setXY(laser.Target().x, laser.Target().y - 10);
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
	utl::uDelayTimer delayTimer;
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