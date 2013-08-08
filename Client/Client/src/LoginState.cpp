#include "stdafx.h"
#include "LoginState.hpp"
#include "CharacterSelectionState.hpp"

using namespace Ogre;

LoginState::LoginState()
{
    mQuit			= false;
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
	Core::getSingletonPtr()->mPlatform = new MyGUI::OgrePlatform();
	Core::getSingletonPtr()->mPlatform->initialise(Core::getSingletonPtr()->mRenderWindow, mSceneManager,"GUI","GUI.txt"); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*

	//Init MyGUI
	Core::getSingletonPtr()->mGUI = new MyGUI::Gui();
	Core::getSingletonPtr()->mGUI->initialise("Core.xml");

	MyGUI::LayoutManager::getInstance().loadLayout("login.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize()); //align loaded forms

	//create pointers to buttons widgets
	MyGUI::ButtonPtr loginButton = Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Button>("loginButton"); //pointer to widget button loaded
	MyGUI::ButtonPtr exitButton = Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Button>("exitButton");

	//event buttons callback
	loginButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressLoginButton);
	exitButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressExitButton);

}

void LoginState::pressLoginButton(MyGUI::Widget* _widget) 
{ 
	//login stuff. for now, i'll be only redirecting to character selection screen
	//get the text from EditBox

/*
	MyGUI::EditBox *loginEditBox = mGUI->findWidget<MyGUI::EditBox>("login");
	MyGUI::EditBox *passwordEditBox = mGUI->findWidget<MyGUI::EditBox>("password");
	String login = loginEditBox->getCaption();

	String password = passwordEditBox->getCaption();
*/
	changeAppState(new CharacterSelectionState());
} 

void LoginState::pressExitButton(MyGUI::Widget* _widget) 
{ 
	mQuit = true;	
} 

void LoginState::exit()
{
	Core::getSingletonPtr()->mGUI->destroyAllChildWidget();
	//free SceneManagers
    mSceneManager->destroyCamera(mCamera);
    if(mSceneManager)Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);
}


bool LoginState::keyPressed(const OIS::KeyEvent &keyEventRef)
{

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
	Core::getSingletonPtr()->mouseMoved(evt);
    return true;
}


bool LoginState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	Core::getSingletonPtr()->mousePressed(evt,id);
    return true;
}


bool LoginState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	Core::getSingletonPtr()->mouseReleased(evt,id);
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