//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	Core.cpp
//

#include "stdafx.h"
#include "Core.hpp"

using namespace Ogre;
template<> Core* Ogre::Singleton<Core>::msSingleton = 0;

Core::Core()
{
    mRoot				= 0;
    mRenderWindow		= 0;
    mViewport			= 0;
    mLog				= 0;
    mTimer				= 0;
    mInputManager		= 0;
    mKeyboard			= 0;
    mMouse				= 0;
	mPlatform			= 0;
	mGUI				= 0;
	mKeyPressed			= OIS::KC_UNASSIGNED; //buffered key, a "hack" to support 2 keys @ same time
	mKeyBuffer			= OIS::KC_UNASSIGNED;
}

Core::~Core()
{
    Core::getSingletonPtr()->mLog->logMessage("Shutdown OGRE...");


	//TODO: Check the OldButGold Segmentation Fault!
	/*
	if(mPlatform){
		mPlatform->shutdown();
		delete mPlatform;
		mPlatform = 0;
	}
	if(mGUI){
		mGUI->shutdown();
		delete mGUI;
		mGUI = 0;
	}
	*/

    if(mInputManager)	OIS::InputManager::destroyInputSystem(mInputManager);
    if(mRoot)			delete mRoot;
}

bool Core::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
	//init GFX
    Ogre::LogManager* logMgr = new Ogre::LogManager();
    mLog = Ogre::LogManager::getSingleton().createLog("GFX.log", true, true, false);
    mLog->setDebugOutputEnabled(true);
    mRoot = new Ogre::Root("plugins.cfg","config.cfg");
	if(!mRoot->restoreConfig()){
		if(!mRoot->showConfigDialog())
			return false;
	}
	//add renderwndw
    mRenderWindow = mRoot->initialise(true, wndTitle);
	//set default viewport
    mViewport = mRenderWindow->addViewport(0);
    mViewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f, 1.0f));
    mViewport->setCamera(0);
    mOverlaySystem = new Ogre::OverlaySystem();

    size_t hWnd = 0;
	OIS::ParamList paramList;

	//--------WIN32 parameters ?-------------
	//TODO: see if in linux works
	mRenderWindow->getCustomAttribute("WINDOW", &hWnd);
	paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
	//-------------------------------------

	mInputManager = OIS::InputManager::createInputSystem(paramList);
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
    mMouse->getMouseState().height = mRenderWindow->getHeight();
    mMouse->getMouseState().width  = mRenderWindow->getWidth();

    if(pKeyListener == 0)mKeyboard->setEventCallback(this);
    else mKeyboard->setEventCallback(pKeyListener);
    if(pMouseListener == 0)mMouse->setEventCallback(this);
    else mMouse->setEventCallback(pMouseListener);

	//init Resource files
    Ogre::String secName, typeName, archName;
    Ogre::ConfigFile cf;
    cf.load("..\\resources.cfg");
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//init Input
    OgreBites::InputContext inputContext;
    inputContext.mMouse = mMouse;
    inputContext.mKeyboard = mKeyboard;
    
	//init Timer
	mTimer = new Ogre::Timer();
    mTimer->reset();

	//init Window
    mRenderWindow->setActive(true);


	//init MyGUI OgrePlatform
	Core::getSingletonPtr()->mPlatform = new MyGUI::OgrePlatform();
	Core::getSingletonPtr()->mPlatform->initialise(Core::getSingletonPtr()->mRenderWindow, NULL,"GUI","GUI.txt"); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*

	//Init MyGUI
	Core::getSingletonPtr()->mGUI = new MyGUI::Gui();
	Core::getSingletonPtr()->mGUI->initialise("Core.xml");

	return true;
}

bool Core::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(mKeyboard->isKeyDown(OIS::KC_SYSRQ))
    {
        mRenderWindow->writeContentsToTimestampedFile("AOF_Screenshot_", ".jpg");
        return true;
    }

	if(mKeyPressed!=keyEventRef.key){
		mKeyBuffer = mKeyPressed;
		mKeyPressed = keyEventRef.key;
	}

	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(keyEventRef.key), keyEventRef.text);
    return true;
}

bool Core::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	//when the key pressed is released, swap with buffer
	if(mKeyPressed==keyEventRef.key){
		mKeyPressed = mKeyBuffer;
		mKeyBuffer = OIS::KC_UNASSIGNED;
	}
	if(mKeyBuffer == keyEventRef.key){ //if the key buffered is released, set him unassigned
		mKeyBuffer = OIS::KC_UNASSIGNED;
	}

	MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(keyEventRef.key));
    return true;
}

bool Core::mouseMoved(const OIS::MouseEvent &evt)
{
	MyGUI::InputManager::getInstance().injectMouseMove(evt.state.X.abs, evt.state.Y.abs, evt.state.Z.abs);
    return true;
}

bool Core::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMousePress(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

bool Core::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMouseRelease(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

void Core::updateOgre(double timeSinceLastFrame)
{

}