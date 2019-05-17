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
#include "uPhysicsManager.h"
#include "uTimer.h"
/*
temporary Game class for testing purposes.
*/
class Game
{
public:
	enum
	{
		INVADER_CLASS = 0x1,
		PLAYER_CLASS  = 0x2,
		LASER_CLASS   = 0x4,
		MISSLE_CLASS  = 0x8
	};
	typedef utl::uGameObject<utl::uPhysicsObject, utl::uSDLRenderObject> GameObject;
	class GameInvader : public GameObject
	{
	public:
		GameInvader() noexcept
		{
			GameObject::Phys._groupId = INVADER_CLASS;
		}
		enum
		{
			A, B, C
		}type;
		bool dead=false;
	};
	class GamePlayer : public GameObject
	{
	public:
		GamePlayer() noexcept
		{
			GameObject::Phys._groupId = PLAYER_CLASS;
			GameObject::Phys.solid = false;
		}
	};
	class GameLaser : public GameObject
	{
	public:
		GameLaser() noexcept
		{
			GameObject::Phys._groupId = LASER_CLASS;
		}
	};



	Game(SDL_Window* window) : timer1ps(1000),timer60ps(17) //17ms ~~ 60 Hz
	{
		//Get viewport dismensions
		SDL_GetWindowSize(window, &displayInfo.w, &displayInfo.h);
	}

	void load()
	{

		const int Padding = procentW(1);
		const int RowHeight = procentH(7);
		const int ColWidth = procentW(7);

		//display grid of invaders
		for (size_t i = 0; i < invaders.size(); i++)
		{
			for (size_t j = 0; j < invaders[i].size(); j++)
			{
				switch (i)
				{
				case 0:
				case 1:
					invaders[i][j].Disp.setImage("res/SPACEC1.png");
					break;
				case 2:
				case 3:
					invaders[i][j].Disp.setImage("res/SPACEB1.png");
					break;
				case 4:
				case 5:
					invaders[i][j].Disp.setImage("res/SPACEA1.png");
					break;
				}
				invaders[i][j].Target().setWH(ColWidth - 10, RowHeight - 5);
				invaders[i][j].Target().setXY((j)*(ColWidth + Padding), (i + 1)*(RowHeight + Padding));
				utl::uDisplayManager::loadObject(&invaders[i][j].Disp);
				physicsManager.addObject(&invaders[i][j].Phys,&invaders[i][j]);
			}
		}

		//Initialise other display objects
		player.Disp.setImage("res/PLAYER.png");
		player.Target().setWH(ColWidth, RowHeight);
		utl::uDisplayManager::loadObject(&player.Disp);
		player.Target().setXY(invaders.front().back().Target().x, invaders.back().back().Target().y + procentH(25));

		laser.Disp.setImage("res/LASER.png");
		laser.Disp.setDefaultWH();
		laser.Disp.setXY(&player.Disp);
		laser.Disp.active = false;
		utl::uDisplayManager::loadObject(&laser.Disp);
		physicsManager.addObject(&laser.Phys,&laser);

		//define keymappings
		handler.on(SDL_KEYDOWN, SDLK_LEFT, [this](SDL_Event* e) {
			player.Target().setXY(player.Target().x - 10, player.Target().y);
			if (player.Target().x < 0) player.Target().setXY(0, player.Target().y);
		});

		handler.on(SDL_KEYDOWN, SDLK_RIGHT, [this](SDL_Event* e) {
			player.Target().setXY(player.Disp.getTarget()->x + 10, player.Disp.getTarget()->y);
			if (player.Disp.getTarget()->x + player.Disp.getTarget()->w > displayInfo.w) player.Target().setXY(displayInfo.w - player.Disp.getTarget()->w, player.Disp.getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_ESCAPE, [this](SDL_Event* e) {
			quit = true;
		});

		handler.on(SDL_KEYDOWN, SDLK_SPACE, [this](SDL_Event* e) {
			if (!shootActive)
			{
				laser.Target().setXY(player.Disp.getTarget()->x + player.Disp.getTarget()->w / 2, player.Disp.getTarget()->y);
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

			auto obj1 = static_cast<Game::GameObject*>(e->user.data1);
			auto obj2 = static_cast<Game::GameObject*>(e->user.data2);

			if (obj1->Phys._groupId == INVADER_CLASS && obj2->Phys._groupId == LASER_CLASS)
			{
				killInvader(static_cast<Game::GameInvader*>(obj1));
				laser.Disp.active = false;
				shootActive = false;
				
			}
			else if (obj2->Phys._groupId == INVADER_CLASS && obj1->Phys._groupId == LASER_CLASS)
			{
				killInvader(static_cast<Game::GameInvader*>(obj2));
				laser.Disp.active = false;
				shootActive = false;
			}
		});
		timer60ps.addCall(1, [this]() { physicsManager.Update(17); });
		timer1ps.addCall(1, [this]() { updateInvaders(); });


	}
	void updateInvaders()
	{
		//get max X
		int stepSize = 10;
		int spaceX = displayInfo.w - invaders[5][11].Target().x - invaders[5][11].Target().w;
		if (spaceX < stepSize) invDir = true;
		if (spaceX > stepSize * 6) invDir = false;
		for (auto& row : invaders)
		{
			for (auto& inv : row)
			{
				if (!inv.dead)
				{
					
				}
				invDir ? inv.Target().x -= stepSize  : inv.Target().x += stepSize;
			}
		}
	}
	void killInvader(GameInvader* obj)
	{
		obj->Disp.setImage("res/BOOM.png");
		obj->Phys.solid = false;
		obj->dead = true;
		delayTimer.DelayCall(250, [obj]() {
			obj->Disp.active = false;
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
		timer1ps.updateTimer();
		delayTimer.updateTimer();
	}
	void shoot()
	{
		laser.Disp.active = true;
		if (laser.Disp.getTarget()->y <= 0)
		{
			laser.Disp.active = false;
			shootActive = false;
		}
		laser.Target().setXY(laser.Target().x, laser.Target().y - 10);
	}

	inline int procentW(int x) noexcept
	{
		const int xx = std::clamp(x, 0, 100);
		const float onePercent = displayInfo.w / 100.0f;
		return (int)onePercent * xx;
	};
	inline int procentH(int x) noexcept
	{
		const int xx = std::clamp(x, 0, 100);
		const float onePercent = displayInfo.h / 100.0f;
		return (int)onePercent * xx;
	};

	std::array<std::array<GameInvader, 12>, 6> invaders;
	GamePlayer player;
	GameLaser laser;
	bool quit = false;
	utl::uInputHandler handler;
	utl::uPhysicsManager physicsManager;
	utl::uSynchronisedTimer timer60ps;
	utl::uSynchronisedTimer timer1ps;
	utl::uDelayTimer delayTimer;
	SDL_DisplayMode displayInfo;
	bool shootActive = false;
	bool pause= false;
	bool invDir = false; // false - right // true - left

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