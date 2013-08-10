//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	CharacterSelectionState.cpp
//

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

	Core::getSingletonPtr()->mLog->logMessage("Entering CharacterSelectionState..."); 

	//setup sceneManager
	mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "CharacterSelectionScreeen");	
	mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
	mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);
	//setup Camera
	mCamera = mSceneManager->createCamera("CharacterSelectionCamera");
	mCamera->setPosition(Vector3(0, 25, -50));
	mCamera->lookAt(Vector3(0, 0, 0));
	mCamera->setNearClipDistance(1);
	mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth())/Real(Core::getSingletonPtr()->mViewport->getActualHeight()));
	Core::getSingletonPtr()->mViewport->setCamera(mCamera);

	createScene();
	initGUI();
}

void CharacterSelectionState::createScene()
{

}

void CharacterSelectionState::initGUI()
{
	Core::getSingletonPtr()->mPlatform->getRenderManagerPtr()->setSceneManager(mSceneManager);
	MyGUI::LayoutManager::getInstance().loadLayout("characterSelection.layout");

	//buttons
	MyGUI::ButtonPtr startButton = Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Button>("startButton"); //pointer to widget button loaded
	//event buttons callback
	startButton->eventMouseButtonClick += MyGUI::newDelegate(this, &CharacterSelectionState::pressStartButton);
}


void CharacterSelectionState::pressStartButton(MyGUI::Widget* _widget)
{
	popAllAndPushAppState(findByName("PlayState"));
}

void CharacterSelectionState::exit()
{
    Core::getSingletonPtr()->mLog->logMessage("Leaving CharacterSelectionState...");
	Core::getSingletonPtr()->mGUI->destroyAllChildWidget();

	mSceneManager->destroyCamera(mCamera);
	if(mSceneManager)Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);

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