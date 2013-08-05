
#ifndef _LoginState_hpp_
#define _LoginState_hpp_

#include "GameState.hpp"

#include "MYGUI/MyGUI.h"
#include "MYGUI/MyGUI_OgrePlatform.h"

class LoginState : public GameState
{
public:
    LoginState();

	DECLARE_STATE(LoginState)

	void enter();
	void initGUI();
	void exit();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

	MyGUI::OgrePlatform*		mPlatform;
	MyGUI::Gui*					mGUI;

	void pressbutton(MyGUI::Widget* _widget);
private:
	bool                        mQuit;
};

#endif