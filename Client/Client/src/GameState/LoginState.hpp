
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