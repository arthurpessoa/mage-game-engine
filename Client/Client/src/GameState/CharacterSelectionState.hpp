
#ifndef CHARACTERSELECTIONSTATE_HPP
#define CHARACTERSELECTIONSTATE_HPP

#include "GameState.hpp"

#include "MYGUI/MyGUI.h"
#include "MYGUI/MyGUI_OgrePlatform.h"

class CharacterSelectionState : public GameState
{
public:
    CharacterSelectionState();

    DECLARE_STATE(CharacterSelectionState)

    void enter();
    void exit();
    void update(double timeSinceLastFrame);

private:
    bool                        m_bQuit;

	MyGUI::OgrePlatform*		mPlatform;
	MyGUI::Gui*					mGUI;
	void initGUI();
	void createScene();
	void pressStartButton(MyGUI::Widget* _widget);

};

#endif
