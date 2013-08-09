#ifndef _Game_hpp_
#define _Game_hpp_

#include "Core.hpp"
#include "GameState\GameStateManager.hpp"

class Client
{
public:
	Client();
	~Client();

	void start();

private:
	GameStateManager*	mAppStateManager;
};

#endif