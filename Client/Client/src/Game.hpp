#ifndef _Game_hpp_
#define _Game_hpp_

#include "Core.hpp"
#include "GameStateManager.hpp"

class Game
{
public:
	Game();
	~Game();

	void start();

private:
	GameStateManager*	mAppStateManager;
};

#endif