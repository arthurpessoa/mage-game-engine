//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	LoginState.cpp
//

#include "stdafx.h"
#include "LoginState.hpp"

using namespace Ogre;

LoginState::LoginState()
{
    mQuit			= false;
    m_FrameEvent    = Ogre::FrameEvent();
}

void LoginState::enter()
{

	Core::getSingletonPtr()->mLog->logMessage("Entering LoginState..."); 
	//setup sceneManager
    mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "LoginSceneManager");	
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
    mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);
	//setup camera
    mCamera = mSceneManager->createCamera("LoginCamera");
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
	Core::getSingletonPtr()->mPlatform->getRenderManagerPtr()->setSceneManager(mSceneManager);
	MyGUI::LayoutManager::getInstance().loadLayout("Login.layout");
	MyGUI::LayoutManager::getInstance().loadLayout("Options.layout");	

	//LoginWIndow
	loginWindow =  Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Window>("loginWindow"); //window
	loginButton = Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Button>("loginButton"); //Login button
	loginButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressLoginButton);	//callback

	//OptionWindow
	optionWindow =  Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Window>("optionWindow"); //window
	optionWindow->setVisible(false);
	exitButton = Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Button>("exitButton"); //Exit button
	exitButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressExitButton); //callback
	/*
	optionButton = Core::getSingletonPtr()->mGUI->findWidget<MyGUI::Button>("optionButton");
	optionButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::pressOptionsButton); //callback
	*/

	//align
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
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
	popAllAndPushAppState(findByName("CharacterSelectionState"));
} 

void LoginState::pressOptionsButton(MyGUI::Widget* _widget)
{
	optionWindow->setVisibleSmooth(true);
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
	Core::getSingletonPtr()->mLog->logMessage("Leaving LoginState...");
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