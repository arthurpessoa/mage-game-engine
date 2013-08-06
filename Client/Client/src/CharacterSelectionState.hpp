
#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "GameState.hpp"

class CharacterSelectionState : public GameState
{
public:
    CharacterSelectionState();

    DECLARE_STATE(CharacterSelectionState)

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
    bool                        m_bQuestionActive;
};

#endif