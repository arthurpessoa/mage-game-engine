#include "stdafx.h"
#include "PlayState.hpp"

using namespace Ogre;

PlayState::PlayState()
{
	m_bQuit             = false;
	m_FrameEvent        = Ogre::FrameEvent();
}

void PlayState::enter()
{
	Core::getSingletonPtr()->mLog->logMessage("Entering PlayState..."); //log

	//setup sceneManager
	mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "PlaySceneManager");
	mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
	mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);
	//setup Camera
	mCamera = mSceneManager->createCamera("charSelect");
	mCamera->setPosition(Vector3(0, 25, -50));
	mCamera->lookAt(Vector3(0, 0, 0));
	mCamera->setNearClipDistance(1);
	mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth()) / Real(Core::getSingletonPtr()->mViewport->getActualHeight()));

	Core::getSingletonPtr()->mViewport->setCamera(mCamera);
	m_bQuit = false;

	createScene();
}


void PlayState::createScene()
{
}

void PlayState::exit()
{
	Core::getSingletonPtr()->mLog->logMessage("Leaving PauseState...");

	mSceneManager->destroyCamera(mCamera);
	if(mSceneManager)
		Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);

}


bool PlayState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	Core::getSingletonPtr()->keyPressed(keyEventRef);
	return true;
}


bool PlayState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	Core::getSingletonPtr()->keyReleased(keyEventRef);

	return true;
}


bool PlayState::mouseMoved(const OIS::MouseEvent &evt)
{
	return true;
}

bool PlayState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PlayState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PlayState::update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	if(m_bQuit == true)
	{
		popAppState();
		return;
	}
}