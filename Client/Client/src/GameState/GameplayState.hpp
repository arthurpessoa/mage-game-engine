
#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include "Player.hpp"
#include "ExtendedCamera.hpp"

#include "MYGUI/MyGUI.h"
#include "MYGUI/MyGUI_OgrePlatform.h"

class GameplayState : public GameState
{
public:
	GameplayState();

	DECLARE_STATE(GameplayState)

	void enter();
	void exit();
	void update(double timeSinceLastFrame);

private:
	bool                        mQuit;
	//Gui System
	MyGUI::OgrePlatform*		mPlatform;
	MyGUI::Gui*					mGUI;
	
	//Player
	Player *mPlayer; //Main Character
	ExtendedCamera *mExtendedCamera; //Track Camera


	void createScene();

	//GUI
	void initGUI();
	void pressStartButton(MyGUI::Widget* _widget);
};
#endif