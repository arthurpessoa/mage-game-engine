#include "stdafx.h"
#include "CharacterSelectionState.hpp"

using namespace Ogre;

CharacterSelectionState::CharacterSelectionState()
{
    m_bQuit             = false;
    m_bQuestionActive   = false;
    m_FrameEvent        = Ogre::FrameEvent();
}

void CharacterSelectionState::enter()
{
    mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "PauseSceneMgr");
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);

    mCamera = mSceneManager->createCamera("charSelect");
    mCamera->setPosition(Vector3(0, 25, -50));
    mCamera->lookAt(Vector3(0, 0, 0));
    mCamera->setNearClipDistance(1);

    mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth()) /  Real(Core::getSingletonPtr()->mViewport->getActualHeight()));
    Core::getSingletonPtr()->mViewport->setCamera(mCamera);


    m_bQuit = false;

    createScene();
}


void CharacterSelectionState::createScene()
{
}

void CharacterSelectionState::exit()
{
    Core::getSingletonPtr()->mLog->logMessage("Leaving PauseState...");

    mSceneManager->destroyCamera(mCamera);
    if(mSceneManager)
        Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);

}


bool CharacterSelectionState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    Core::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}


bool CharacterSelectionState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    Core::getSingletonPtr()->keyReleased(keyEventRef);

    return true;
}


bool CharacterSelectionState::mouseMoved(const OIS::MouseEvent &evt)
{
    return true;
}

bool CharacterSelectionState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}


bool CharacterSelectionState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
     return true;
}

void CharacterSelectionState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    if(m_bQuit == true)
    {
        popAppState();
        return;
    }
}