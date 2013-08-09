//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	Client.cpp
//
#include "stdafx.h"
#include "Client.hpp"
#include "GameState\LoginState.hpp"
#include "GameState\PlayState.hpp"
#include "GameState\CharacterSelectionState.hpp"

Client::Client()
{
	mAppStateManager = 0;
}

Client::~Client()
{
	delete mAppStateManager;
    delete Core::getSingletonPtr();
}

void Client::start()
{
	//init Game Core
	new Core();
	if(!Core::getSingletonPtr()->initOgre("Client", 0, 0))	return;

	//start State Manager
	mAppStateManager = new GameStateManager();
	//create the game States
	LoginState::create(mAppStateManager, "LoginState");
	CharacterSelectionState::create(mAppStateManager, "CharacterSelectionState");
	PlayState::create(mAppStateManager,"PlayState");

	//go to first state, LoginScreen
	mAppStateManager->start(mAppStateManager->findByName("LoginState"));
}

// -------------------------------------------------------
//					Client Application Entrance
// ------------------------------------------------------

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	Client game;
	try
	{
		game.start();
	}
	catch(std::exception& e)
	{
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occurred: %s\n", e.what());
#endif
	}
	return 0;
}
