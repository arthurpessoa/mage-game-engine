
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
}

Core::~Core()
{
    Core::getSingletonPtr()->mLog->logMessage("Shutdown OGRE...");
    if(mInputManager)		OIS::InputManager::destroyInputSystem(mInputManager);
    if(mRoot)			delete mRoot;
}

bool Core::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
    Ogre::LogManager* logMgr = new Ogre::LogManager();

    mLog = Ogre::LogManager::getSingleton().createLog("GFX.log", true, true, false);
    mLog->setDebugOutputEnabled(true);

    mRoot = new Ogre::Root("plugins.cfg","config.cfg");

	if(!mRoot->restoreConfig()){
		if(!mRoot->showConfigDialog())
			return false;
	}
    mRenderWindow = mRoot->initialise(true, wndTitle);

    mViewport = mRenderWindow->addViewport(0);
    mViewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f, 1.0f));

    mViewport->setCamera(0);

    mOverlaySystem = new Ogre::OverlaySystem();

    size_t hWnd = 0;
    OIS::ParamList paramList;
    mRenderWindow->getCustomAttribute("WINDOW", &hWnd);
    paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
    mInputManager = OIS::InputManager::createInputSystem(paramList);
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
    mMouse->getMouseState().height = mRenderWindow->getHeight();
    mMouse->getMouseState().width	 = mRenderWindow->getWidth();

    if(pKeyListener == 0)mKeyboard->setEventCallback(this);
    else mKeyboard->setEventCallback(pKeyListener);
    if(pMouseListener == 0)mMouse->setEventCallback(this);
    else mMouse->setEventCallback(pMouseListener);

	//Load Resource files
    Ogre::String secName, typeName, archName;
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");

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

    OgreBites::InputContext inputContext;
    inputContext.mMouse = mMouse;
    inputContext.mKeyboard = mKeyboard;

    mTimer = new Ogre::Timer();
    mTimer->reset();

    mRenderWindow->setActive(true);

    return true;
}

bool Core::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(mKeyboard->isKeyDown(OIS::KC_SYSRQ))
    {
        mRenderWindow->writeContentsToTimestampedFile("AOF_Screenshot_", ".jpg");
        return true;
    }

    return true;
}

bool Core::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    return true;
}

bool Core::mouseMoved(const OIS::MouseEvent &evt)
{
    return true;
}

bool Core::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

bool Core::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

void Core::updateOgre(double timeSinceLastFrame)
{

}