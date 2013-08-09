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
//  based in Kencho version (Ogre3D forum)
//	The GameObject class is used to define every object that can be 
//	tracked and chased by a camera

#include "Core.hpp"

// Generic GameObject class
class GameObject {
protected:
	Ogre::SceneNode *mMainNode; // Main character node
	Ogre::SceneNode *mSightNode; // "Sight" node - The character is supposed to be looking here
	Ogre::SceneNode *mCameraNode; // Node for the chase camera
	Ogre::Entity *mEntity; // Character entity
	Ogre::SceneManager *mSceneMgr;
public:
	// Updates the character (movement...)
	virtual void update (Ogre::Real elapsedTime, OIS::Keyboard *input) = 0;
	// The three methods below returns the two camera-related nodes, 
	// and the current position of the character (for the 1st person camera)
	Ogre::SceneNode *getSightNode () {
		return mSightNode;
	}
	Ogre::SceneNode *getCameraNode () {
		return mCameraNode;
	}
	Ogre::Vector3 getWorldPosition () {
		return mMainNode->_getDerivedPosition ();
	}
};