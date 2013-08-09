
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

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

private:
	bool                        m_bQuit;

	MyGUI::OgrePlatform*		mPlatform;
	MyGUI::Gui*					mGUI;

	Player *mPlayer;
	ExtendedCamera *mExtendedCamera;
	unsigned short int mCameraMode;

	void createScene();

	//GUI
	void initGUI();
	void pressStartButton(MyGUI::Widget* _widget);
};
#endif