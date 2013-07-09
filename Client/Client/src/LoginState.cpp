#include "stdafx.h"
#include "LoginState.hpp"


using namespace Ogre;

LoginState::LoginState()
{
    m_bQuit         = false;
    m_FrameEvent    = Ogre::FrameEvent();
}

void LoginState::enter()
{
    mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "LoginSceneMgr");
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
    mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);
    mCamera = mSceneManager->createCamera("MenuCam");
    mCamera->setPosition(Vector3(0, 25, -50));
    mCamera->lookAt(Vector3(0, 0, 0));
    mCamera->setNearClipDistance(1);

    mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth())/Real(Core::getSingletonPtr()->mViewport->getActualHeight()));
    Core::getSingletonPtr()->mViewport->setCamera(mCamera);
	createScene();
}

void LoginState::createScene()
{


}


void LoginState::exit()
{
    mSceneManager->destroyCamera(mCamera);
    if(mSceneManager)
        Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);
}


bool LoginState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(Core::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        m_bQuit = true;
        return true;
    }

    Core::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}


bool LoginState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    Core::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}


bool LoginState::mouseMoved(const OIS::MouseEvent &evt)
{

    return true;
}


bool LoginState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

    return true;
}


bool LoginState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

    return true;
}

void LoginState::update(double timeSinceLastFrame)
{
	
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    
    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
}