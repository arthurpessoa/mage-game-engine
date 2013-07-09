
#include "stdafx.h"
#include "Core.hpp"

using namespace Ogre;
template<> Core* Ogre::Singleton<Core>::msSingleton = 0;

Core::Core()
{
    mRoot				= 0;
    m_pRenderWnd		= 0;
    mViewport			= 0;
    m_pLog				= 0;
    m_pTimer			= 0;

    m_pInputMgr			= 0;
    m_pKeyboard			= 0;
    m_pMouse			= 0;
}

Core::~Core()
{
    Core::getSingletonPtr()->m_pLog->logMessage("Shutdown OGRE...");
    if(m_pInputMgr)		OIS::InputManager::destroyInputSystem(m_pInputMgr);
    if(mRoot)			delete mRoot;
}

bool Core::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
    Ogre::LogManager* logMgr = new Ogre::LogManager();

    m_pLog = Ogre::LogManager::getSingleton().createLog("GFX.log", true, true, false);
    m_pLog->setDebugOutputEnabled(true);

    mRoot = new Ogre::Root("plugins.cfg","config.cfg");

    if(!mRoot->showConfigDialog())
        return false;
    m_pRenderWnd = mRoot->initialise(true, wndTitle);

    mViewport = m_pRenderWnd->addViewport(0);
    mViewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f, 1.0f));

    mViewport->setCamera(0);

    mOverlaySystem = new Ogre::OverlaySystem();

    size_t hWnd = 0;
    OIS::ParamList paramList;
    m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);
    paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
    m_pInputMgr = OIS::InputManager::createInputSystem(paramList);
    m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
    m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));
    m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
    m_pMouse->getMouseState().width	 = m_pRenderWnd->getWidth();

    if(pKeyListener == 0)m_pKeyboard->setEventCallback(this);
    else m_pKeyboard->setEventCallback(pKeyListener);
    if(pMouseListener == 0)m_pMouse->setEventCallback(this);
    else m_pMouse->setEventCallback(pMouseListener);



	/*Load Resource files*/

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
    inputContext.mMouse = m_pMouse;
    inputContext.mKeyboard = m_pKeyboard;

    m_pTimer = new Ogre::Timer();
    m_pTimer->reset();

    m_pRenderWnd->setActive(true);

    return true;
}

bool Core::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ))
    {
        m_pRenderWnd->writeContentsToTimestampedFile("AOF_Screenshot_", ".jpg");
        return true;
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool Core::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool Core::mouseMoved(const OIS::MouseEvent &evt)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool Core::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool Core::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

void Core::updateOgre(double timeSinceLastFrame)
{
}