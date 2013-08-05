#include "stdafx.h"

#include "Game.hpp"

#include "LoginState.hpp"
#include "PlayState.hpp"
#include "PauseState.hpp"

Game::Game()
{
	mAppStateManager = 0;
}

Game::~Game()
{
	delete mAppStateManager;
    delete Core::getSingletonPtr();
}

void Game::start()
{
	new Core();
	if(!Core::getSingletonPtr()->initOgre("Client", 0, 0))	return;


	mAppStateManager = new GameStateManager();
	LoginState::create(mAppStateManager, "LoginScreen");

	mAppStateManager->start(mAppStateManager->findByName("LoginScreen"));
}
