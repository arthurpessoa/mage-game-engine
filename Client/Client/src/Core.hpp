//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	Arthur Pessoa
//


#ifndef _Core_hpp_
#define _Core_hpp_

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreConfigFile.h>
#include "OGRE/Overlay/OgreOverlay.h"

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include "MYGUI/MyGUI.h"
#include "MYGUI/MyGUI_OgrePlatform.h"

class Core : public Ogre::Singleton<Core>, OIS::KeyListener, OIS::MouseListener
{
public:
	Core();
	~Core();

	//Ogre
	Ogre::Root*					mRoot;
	Ogre::RenderWindow*			mRenderWindow;
	Ogre::Viewport*				mViewport;
	Ogre::Log*					mLog;
	Ogre::Timer*				mTimer;
	Ogre::OverlaySystem*        mOverlaySystem;
	bool initOgre(Ogre::String windowTitle, OIS::KeyListener *mKeyListener = 0, OIS::MouseListener *mMouseListener = 0);
	void updateOgre(double timeSinceLastFrame);

	//Input System
	OIS::InputManager*			mInputManager;
	OIS::Keyboard*				mKeyboard;
	OIS::Mouse*					mMouse;
	OIS::KeyCode				mKeyPressed;
	OIS::KeyCode				mKeyBuffer;
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	//GUI System
	MyGUI::OgrePlatform*		mPlatform;
	MyGUI::Gui*					mGUI;

private:
	Core(const Core&);
	Core& operator= (const Core&);
};

#endif