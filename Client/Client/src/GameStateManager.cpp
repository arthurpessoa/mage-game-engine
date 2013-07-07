#include "stdafx.h"
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameStateManager.hpp"

#include <OgreWindowEventUtilities.h>

//|||||||||||||||||||||||||||||||||||||||||||||||

GameStateManager::GameStateManager()
{
	m_bShutdown = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

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

void GameStateManager::manageAppState(Ogre::String stateName, AppState* state)
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

//|||||||||||||||||||||||||||||||||||||||||||||||

AppState* GameStateManager::findByName(Ogre::String stateName)
{
	std::vector<state_info>::iterator itr;

	for(itr=m_States.begin();itr!=m_States.end();itr++)
	{
		if(itr->name==stateName)
			return itr->state;
	}

	return 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameStateManager::start(AppState* state)
{
	changeAppState(state);

	int timeSinceLastFrame = 1;
	int startTime = 0;

	while(!m_bShutdown)
	{
		if(Core::getSingletonPtr()->m_pRenderWnd->isClosed())m_bShutdown = true;

		Ogre::WindowEventUtilities::messagePump();

		if(Core::getSingletonPtr()->m_pRenderWnd->isActive())
		{
			startTime = Core::getSingletonPtr()->m_pTimer->getMillisecondsCPU();

			Core::getSingletonPtr()->m_pKeyboard->capture();
			Core::getSingletonPtr()->m_pMouse->capture();

			m_ActiveStateStack.back()->update(timeSinceLastFrame);

			Core::getSingletonPtr()->updateOgre(timeSinceLastFrame);
			Core::getSingletonPtr()->m_pRoot->renderOneFrame();

			timeSinceLastFrame = Core::getSingletonPtr()->m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}

	Core::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
}


void GameStateManager::changeAppState(AppState* state)
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


bool GameStateManager::pushAppState(AppState* state)
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

void GameStateManager::popAllAndPushAppState(AppState* state)
{
    while(!m_ActiveStateStack.empty())
    {
        m_ActiveStateStack.back()->exit();
        m_ActiveStateStack.pop_back();
    }

    pushAppState(state);
}

void GameStateManager::pauseAppState()
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


void GameStateManager::init(AppState* state)
{
    Core::getSingletonPtr()->m_pKeyboard->setEventCallback(state);
	Core::getSingletonPtr()->m_pMouse->setEventCallback(state);
    Core::getSingletonPtr()->m_pTrayMgr->setListener(state);
	Core::getSingletonPtr()->m_pRenderWnd->resetStatistics();
}
