#include "stdafx.h"
#include "LoginState.hpp"

using namespace Ogre;

LoginState::LoginState()
{
    mQuit         = false;
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

	initGUI();
}

void LoginState::initGUI()
{
	//init MyGUI OgrePlatform
	mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(Core::getSingletonPtr()->mRenderWindow, mSceneManager); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*
	//Init MyGUI
	mGUI = new MyGUI::Gui();
	mGUI->initialise();
	
	//button test

	MyGUI::WindowPtr window = MyGUI::Gui::getInstance().createWidget<MyGUI::Window>("WindowC", 10, 1, 390, 300, MyGUI::Align::Default, "Overlapped"); 
	MyGUI::ButtonPtr button = mGUI->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	
	button->setCaption("exit");
	button->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressbutton);

	 MyGUI::PointerManager::getInstance().setVisible(true);

	
}

void LoginState::pressbutton(MyGUI::Widget* _widget) 
{ 
	mQuit = true;	
} 

void LoginState::exit()
{
    mSceneManager->destroyCamera(mCamera);
    if(mSceneManager)
        Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);
}


bool LoginState::keyPressed(const OIS::KeyEvent &keyEventRef)
{

	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(keyEventRef.key), keyEventRef.text);
	if(Core::getSingletonPtr()->mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        mQuit = true;
        return true;
    }

    Core::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}


bool LoginState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(keyEventRef.key));
    Core::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}


bool LoginState::mouseMoved(const OIS::MouseEvent &evt)
{
	MyGUI::InputManager::getInstance().injectMouseMove(evt.state.X.abs, evt.state.Y.abs, evt.state.Z.abs);
    return true;
}


bool LoginState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMousePress(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}


bool LoginState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMouseRelease(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

void LoginState::update(double timeSinceLastFrame)
{
	
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    
    if(mQuit == true)
    {
        shutdown();
        return;
    }
}