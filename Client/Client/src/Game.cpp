#include "stdafx.h"

#include "Game.hpp"

#include "MenuState.hpp"
#include "GameState.hpp"
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
	if(!Core::getSingletonPtr()->initOgre("AdvancedOgreFramework", 0, 0))	return;

	m_pAppStateManager = new GameStateManager();
	MenuState::create(m_pAppStateManager, "MenuState");
	GameState::create(m_pAppStateManager, "GameState");
    PauseState::create(m_pAppStateManager, "PauseState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("MenuState"));
}
