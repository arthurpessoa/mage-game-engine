#include "stdafx.h"
#include "CharacterSelectionState.hpp"

using namespace Ogre;

CharacterSelectionState::CharacterSelectionState()
{
    m_bQuit             = false;
    m_FrameEvent        = Ogre::FrameEvent();
}

void CharacterSelectionState::enter()
{
    m_bQuit = false;

	mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "CharacterSelectionScreeen");	
	mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
	mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);

	mCamera = mSceneManager->createCamera("CharacterSelectionCamera");
	mCamera->setPosition(Vector3(0, 25, -50));
	mCamera->lookAt(Vector3(0, 0, 0));
	mCamera->setNearClipDistance(1);
	mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth())/Real(Core::getSingletonPtr()->mViewport->getActualHeight()));
	Core::getSingletonPtr()->mViewport->setCamera(mCamera);

	initGUI();
}

void CharacterSelectionState::initGUI()
{
	Core::getSingletonPtr()->mPlatform->getRenderManagerPtr()->setSceneManager(mSceneManager);
}



void CharacterSelectionState::createScene()
{
}

void CharacterSelectionState::exit()
{
    Core::getSingletonPtr()->mLog->logMessage("Leaving PauseState...");
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
	Core::getSingletonPtr()->mouseMoved(evt);
	return true;
}


bool CharacterSelectionState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	Core::getSingletonPtr()->mousePressed(evt,id);
	return true;
}


bool CharacterSelectionState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	Core::getSingletonPtr()->mouseReleased(evt,id);
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