#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP

#include "Core.hpp"
#include "GameStateManager.hpp"

class Game
{
public:
	Game();
	~Game();

	void start();

private:
	GameStateManager*	m_pAppStateManager;
};

#endif