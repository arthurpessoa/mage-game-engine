//   ___      ___       __       _______    _______  
//  |"  \    /"  |     /""\     /" _   "|  /"     "| 
//   \   \  //   |    /    \   (: ( \___) (: ______) 
//   /\\  \/.    |   /' /\  \   \/ \       \/    |   
//  |: \.        |  //  __'  \  //  \ ___  // ___)_  
//  |.  \    /:  | /   /  \\  \(:   _(  _|(:      "| 
//  |___|\__/|___|(___/    \___)\_______)  \_______) 
//
//	Player.cpp
//

#include "stdafx.h"
#include "Player.hpp"

Player::Player (Ogre::String name, Ogre::SceneManager *sceneMgr) {
	// Setup basic member references
	mName = name;
	mSceneMgr = sceneMgr;

	// Setup basic node structure to handle 3rd person cameras
	mMainNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode (mName);
	mSightNode = mMainNode->createChildSceneNode (mName + "_sight", Ogre::Vector3 (0, 0, 100));
	mCameraNode = mMainNode->createChildSceneNode (mName + "_camera", Ogre::Vector3 (0, 50, -100));

	// Give this character a shape :)
	mEntity = mSceneMgr->createEntity (mName, "OgreHead.mesh");
	mMainNode->attachObject (mEntity);
	
}

Player::~Player () {
	mMainNode->detachAllObjects ();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren ();
	mSceneMgr->destroySceneNode (mName);
}

void Player::update (Ogre::Real elapsedTime) {
	// Handle movement
	
	
	if (Core::getSingletonPtr()->mKeyPressed == (OIS::KC_W)) {
		mMainNode->translate (mMainNode->getOrientation () * Ogre::Vector3 (0, 0, 100 * (elapsedTime/1000)));

	}
	if (Core::getSingletonPtr()->mKeyPressed == (OIS::KC_S)) {
		mMainNode->translate (mMainNode->getOrientation () * Ogre::Vector3 (0, 0, -50 * (elapsedTime/1000)));
	}
	if (Core::getSingletonPtr()->mKeyPressed == (OIS::KC_A)) {
		mMainNode->yaw (Ogre::Radian (2 * (elapsedTime/1000)));
	}
	if (Core::getSingletonPtr()->mKeyPressed == (OIS::KC_D)) {
		mMainNode->yaw (Ogre::Radian (-2 * (elapsedTime/1000)));
	}
}

// Change visibility - Useful for 1st person view ;)
void Player::setVisible (bool visible) {
	mMainNode->setVisible (visible);
}
