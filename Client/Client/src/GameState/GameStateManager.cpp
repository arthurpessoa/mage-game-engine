//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	GameStateManager.cpp
//

#include "stdafx.h"

#include "GameStateManager.hpp"
#include <OGRE/OgreWindowEventUtilities.h>

GameStateManager::GameStateManager()
{
	m_bShutdown = false;
}

GameStateManager::~GameStateManager()
{
	state_info si;

    while(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}

	while(!m_States.empty())
	{
		si = m_States.back();
        si.state->destroy();
        m_States.pop_back();
	}
}

void GameStateManager::manageState(Ogre::String stateName, GameState* state)
{
	try
	{
		state_info new_state_info;
		new_state_info.name = stateName;
		new_state_info.state = state;
		m_States.push_back(new_state_info);
	}
	catch(std::exception& e)
	{
		delete state;
		throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "Error while trying to manage a new AppState\n" + Ogre::String(e.what()), "AppStateManager.cpp (39)");
	}
}

GameState* GameStateManager::findByName(Ogre::String stateName)
{
	std::vector<state_info>::iterator itr;

	for(itr=m_States.begin();itr!=m_States.end();itr++)
	{
		if(itr->name==stateName)
			return itr->state;
	}

	return 0;
}

void GameStateManager::start(GameState* state)
{
	changeState(state);

	int timeSinceLastFrame = 1;
	int startTime = 0;

	while(!m_bShutdown)
	{

		try{
			if(Core::getSingletonPtr()->mRenderWindow->isClosed())m_bShutdown = true;

			Ogre::WindowEventUtilities::messagePump();

			if(Core::getSingletonPtr()->mRenderWindow->isActive())
			{
				startTime = Core::getSingletonPtr()->mTimer->getMillisecondsCPU();

				Core::getSingletonPtr()->mKeyboard->capture();
				Core::getSingletonPtr()->mMouse->capture();

				m_ActiveStateStack.back()->update(timeSinceLastFrame);

				Core::getSingletonPtr()->updateOgre(timeSinceLastFrame);
				Core::getSingletonPtr()->mRoot->renderOneFrame();
				timeSinceLastFrame = Core::getSingletonPtr()->mTimer->getMillisecondsCPU() - startTime;
			}		
		}catch(std::exception& e)
		{
			delete state;
			throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, e.what(), "GameStateManager.cpp (39)");
		}
	}
}

void GameStateManager::changeState(GameState* state)
{
	if(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}

	m_ActiveStateStack.push_back(state);
	init(state);
	m_ActiveStateStack.back()->enter();
}


bool GameStateManager::pushState(GameState* state)
{
	if(!m_ActiveStateStack.empty())
	{
		if(!m_ActiveStateStack.back()->pause())
			return false;
	}

	m_ActiveStateStack.push_back(state);
	init(state);
	m_ActiveStateStack.back()->enter();

	return true;
}

void GameStateManager::popAppState()
{
	if(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}

	if(!m_ActiveStateStack.empty())
	{
		init(m_ActiveStateStack.back());
		m_ActiveStateStack.back()->resume();
	}
    else
		shutdown();
}

void GameStateManager::popAllAndPushState(GameState* state)
{
    while(!m_ActiveStateStack.empty())
    {
        m_ActiveStateStack.back()->exit();
        m_ActiveStateStack.pop_back();
    }

    pushState(state);
}

void GameStateManager::pauseState()
{
	if(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->pause();
	}

	if(m_ActiveStateStack.size() > 2)
	{
		init(m_ActiveStateStack.at(m_ActiveStateStack.size() - 2));
		m_ActiveStateStack.at(m_ActiveStateStack.size() - 2)->resume();
	}
}

void GameStateManager::shutdown()
{
	m_bShutdown = true;
}


void GameStateManager::init(GameState* state)
{
    Core::getSingletonPtr()->mKeyboard->setEventCallback(state);
	Core::getSingletonPtr()->mMouse->setEventCallback(state);
	Core::getSingletonPtr()->mRenderWindow->resetStatistics();
}