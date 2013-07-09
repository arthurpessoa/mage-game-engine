#include "stdafx.h"
#include "PauseState.hpp"

using namespace Ogre;

PauseState::PauseState()
{
    m_bQuit             = false;
    m_bQuestionActive   = false;
    m_FrameEvent        = Ogre::FrameEvent();
}

void PauseState::enter()
{
    Core::getSingletonPtr()->m_pLog->logMessage("Entering PauseState...");

    mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "PauseSceneMgr");
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);

    mCamera = mSceneManager->createCamera("PauseCam");
    mCamera->setPosition(Vector3(0, 25, -50));
    mCamera->lookAt(Vector3(0, 0, 0));
    mCamera->setNearClipDistance(1);

    mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth()) /
        Real(Core::getSingletonPtr()->mViewport->getActualHeight()));

    Core::getSingletonPtr()->mViewport->setCamera(mCamera);


    m_bQuit = false;

    createScene();
}


void PauseState::createScene()
{
}

void PauseState::exit()
{
    Core::getSingletonPtr()->m_pLog->logMessage("Leaving PauseState...");

    mSceneManager->destroyCamera(mCamera);
    if(mSceneManager)
        Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);

}


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


bool PauseState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    Core::getSingletonPtr()->keyReleased(keyEventRef);

    return true;
}


bool PauseState::mouseMoved(const OIS::MouseEvent &evt)
{
    return true;
}

bool PauseState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
     return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    if(m_bQuit == true)
    {
        popAppState();
        return;
    }
}