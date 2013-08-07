#include "stdafx.h"
#include "LoginState.hpp"
#include "CharacterSelectionState.hpp"

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
	mPlatform->initialise(Core::getSingletonPtr()->mRenderWindow, mSceneManager,"GUI","GUI.txt"); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*

	//Init MyGUI
	mGUI = new MyGUI::Gui();
	mGUI->initialise("Core.xml");

	MyGUI::LayoutManager::getInstance().loadLayout("login.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize()); //align loaded forms

	//create pointers to buttons widgets
	MyGUI::ButtonPtr loginButton = mGUI->findWidget<MyGUI::Button>("loginButton"); //pointer to widget button loaded
	MyGUI::ButtonPtr exitButton = mGUI->findWidget<MyGUI::Button>("exitButton");

	//event buttons callback
	loginButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressLoginButton);
	exitButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressExitButton);
}

void LoginState::pressLoginButton(MyGUI::Widget* _widget) 
{ 
	//login stuff. for now, i'll be only redirecting to character selection screen
	//get the text from EditBox
	MyGUI::EditBox *loginEditBox = mGUI->findWidget<MyGUI::EditBox>("login");
	MyGUI::EditBox *passwordEditBox = mGUI->findWidget<MyGUI::EditBox>("password");
	String login = loginEditBox->getCaption();
	String password = passwordEditBox->getCaption();

	changeAppState(new CharacterSelectionState());
} 

void LoginState::pressExitButton(MyGUI::Widget* _widget) 
{ 
	mQuit = true;	
} 

void LoginState::exit()
{
	//free GUI System
	mGUI->shutdown();
	delete mGUI;
	mGUI=0;
	mPlatform->shutdown();
	delete mPlatform;
	mPlatform=0;
	
	//free SceneManagers
    mSceneManager->destroyCamera(mCamera);
    if(mSceneManager)Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);

}


bool LoginState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(keyEventRef.key), keyEventRef.text);
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