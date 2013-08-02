#ifndef _Core_hpp_
#define _Core_hpp_

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/Overlay/OgreOverlay.h>
#include <OGRE/Overlay/OgreOverlayElement.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreConfigFile.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

class Core : public Ogre::Singleton<Core>, OIS::KeyListener, OIS::MouseListener
{
public:
	Core();
	~Core();

	bool initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener = 0, OIS::MouseListener *pMouseListener = 0);
	void updateOgre(double timeSinceLastFrame);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	Ogre::Root*					mRoot;
	Ogre::RenderWindow*			mRenderWindow;
	Ogre::Viewport*				mViewport;
	Ogre::Log*					mLog;
	Ogre::Timer*				mTimer;
	OIS::InputManager*			mInputManager;
	OIS::Keyboard*				mKeyboard;
	OIS::Mouse*					mMouse;
    Ogre::OverlaySystem*        mOverlaySystem;

private:
	Core(const Core&);
	Core& operator= (const Core&);
};

#endif