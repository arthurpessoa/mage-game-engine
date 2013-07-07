//|||||||||||||||||||||||||||||||||||||||||||||||

#include "stdafx.h"
#include "PauseState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

PauseState::PauseState()
{
    m_bQuit             = false;
    m_bQuestionActive   = false;
    m_FrameEvent        = Ogre::FrameEvent();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::enter()
{
    Core::getSingletonPtr()->m_pLog->logMessage("Entering PauseState...");

    m_pSceneMgr = Core::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "PauseSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pSceneMgr->addRenderQueueListener(Core::getSingletonPtr()->m_pOverlaySystem);

    m_pCamera = m_pSceneMgr->createCamera("PauseCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(Core::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(Core::getSingletonPtr()->m_pViewport->getActualHeight()));

    Core::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    Core::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    Core::getSingletonPtr()->m_pTrayMgr->showCursor();
    Core::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToGameBtn", "Return to GameState", 250);
    Core::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToMenuBtn", "Return to Menu", 250);
    Core::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit AdvancedOgreFramework", 250);
    Core::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "PauseLbl", "Pause mode", 250);

    m_bQuit = false;

    createScene();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::createScene()
{
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::exit()
{
    Core::getSingletonPtr()->m_pLog->logMessage("Leaving PauseState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        Core::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

    Core::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    Core::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    Core::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(Core::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE) && !m_bQuestionActive)
    {
        m_bQuit = true;
        return true;
    }

    Core::getSingletonPtr()->keyPressed(keyEventRef);

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    Core::getSingletonPtr()->keyReleased(keyEventRef);

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::mouseMoved(const OIS::MouseEvent &evt)
{
    if(Core::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(Core::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(Core::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    Core::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::buttonHit(OgreBites::Button *button)
{
    if(button->getName() == "ExitBtn")
    {
        Core::getSingletonPtr()->m_pTrayMgr->showYesNoDialog("Sure?", "Really leave?");
        m_bQuestionActive = true;
    }
    else if(button->getName() == "BackToGameBtn")
        m_bQuit = true;
    else if(button->getName() == "BackToMenuBtn")
        popAllAndPushAppState(findByName("MenuState"));
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit)
{
    if(yesHit == true)
        shutdown();
    else
        Core::getSingletonPtr()->m_pTrayMgr->closeDialog();

    m_bQuestionActive = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||