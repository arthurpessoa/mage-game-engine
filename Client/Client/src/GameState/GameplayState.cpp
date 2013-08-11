//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	PlayState.cpp
//

#include "stdafx.h"
#include "GameplayState.hpp"

using namespace Ogre;

GameplayState::GameplayState()
{
	mQuit             = false;
	mPlayer				= 0;
	mExtendedCamera		= 0;
	mCamera				= 0;
	m_FrameEvent        = Ogre::FrameEvent();
}

void GameplayState::enter()
{
	Core::getSingletonPtr()->mLog->logMessage("Entering GameplayState..."); //log

	//setup sceneManager
	mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "PlaySceneManager");
	mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);
	//setup Camera
	mCamera = mSceneManager->createCamera("charSelect");
	mCamera->lookAt(Vector3(0, 0, 0));
	mCamera->setNearClipDistance(1);
	mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth()) / Real(Core::getSingletonPtr()->mViewport->getActualHeight()));

	Core::getSingletonPtr()->mViewport->setCamera(mCamera);

	mQuit = false;

	createScene();
}


void GameplayState::createScene()
{
	// Set ambient light
	mSceneManager->setAmbientLight(ColourValue(0.2f, 0.2f, 0.2f));

	// LIGHTS!!
	// Create a point light
	Light* l = mSceneManager->createLight("MainLight");

	// Accept default settings: point light, white diffuse, just set position
	// NB I could attach the light to a SceneNode if I wanted it to move automatically with
	//  other objects, but I don't
	l->setType(Light::LT_DIRECTIONAL);
	l->setDirection(-0.5, -0.5, 0);

	// CAMERA!!
	mCamera->setPosition(0, 0, 0);    // Required or else the camera will have an offset

	// Main character
	mPlayer = new Player("Ogre 1", mSceneManager);
	mPlayer->setVisible (true);

	mExtendedCamera = new ExtendedCamera ("Extended Camera", mSceneManager, mCamera);
	mExtendedCamera->setTightness(0);


	if (mPlayer)
		static_cast<Player *>(mPlayer)->setVisible (true);
	if (mExtendedCamera) {
		if (mPlayer)
			mExtendedCamera->instantUpdate (mPlayer->getCameraNode ()->_getDerivedPosition(), mPlayer->getSightNode ()->_getDerivedPosition());
			mExtendedCamera->setTightness (0.01f);
	}

}

void GameplayState::exit()
{
	Core::getSingletonPtr()->mLog->logMessage("Leaving GameplayState...");

	mSceneManager->destroyCamera(mCamera);
	if(mSceneManager)
		Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);

}


bool GameplayState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	Core::getSingletonPtr()->keyPressed(keyEventRef);
	return true;
}


bool GameplayState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	Core::getSingletonPtr()->keyReleased(keyEventRef);
	return true;
}


bool GameplayState::mouseMoved(const OIS::MouseEvent &evt)
{
	return true;
}

bool GameplayState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}


bool GameplayState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}


void GameplayState::update(double timeSinceLastFrame)
{

	if (mPlayer) {
		mPlayer->update (timeSinceLastFrame);
		if(mExtendedCamera){
			mExtendedCamera->update(timeSinceLastFrame,mPlayer->getCameraNode ()->_getDerivedPosition(), mPlayer->getSightNode ()->_getDerivedPosition());
		}
	}

	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	if(mQuit == true)
	{
		shutdown();
		return;
	}
}