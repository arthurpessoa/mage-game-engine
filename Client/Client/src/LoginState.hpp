
#ifndef _LoginState_hpp_
#define _LoginState_hpp_

#include "GameState.hpp"

class LoginState : public GameState
{
public:
    LoginState();

	DECLARE_STATE(LoginState)

	void enter();
	void createScene();
	void exit();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

private:
	bool                        m_bQuit;
};

#endif