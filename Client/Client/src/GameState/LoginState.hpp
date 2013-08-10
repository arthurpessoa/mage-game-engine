
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
	void exit();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

	

private:
	bool                        mQuit;
	void initGUI();

	//GUI
	MyGUI::WindowPtr loginWindow;//loginWindow Widgets
	MyGUI::ButtonPtr loginButton;
	MyGUI::ButtonPtr optionButton; //optionWindow widgets
	MyGUI::WindowPtr optionWindow;
	MyGUI::ButtonPtr exitButton; //menuWindow Widgets

	void pressLoginButton(MyGUI::Widget* _widget);
	void pressExitButton(MyGUI::Widget* _widget);
	void pressOptionsButton(MyGUI::Widget* _widget);
};

#endif