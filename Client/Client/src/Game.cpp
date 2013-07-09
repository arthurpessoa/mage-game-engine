#include "stdafx.h"

#include "Game.hpp"

#include "LoginState.hpp"
#include "PlayState.hpp"
#include "PauseState.hpp"

Game::Game()
{
	m_pAppStateManager = 0;
}

Game::~Game()
{
	delete m_pAppStateManager;
    delete Core::getSingletonPtr();
}

void Game::start()
{
	new Core();
	if(!Core::getSingletonPtr()->initOgre("Client", 0, 0))	return;


	m_pAppStateManager = new GameStateManager();
	LoginState::create(m_pAppStateManager, "LoginScreen");

	m_pAppStateManager->start(m_pAppStateManager->findByName("LoginScreen"));
}
