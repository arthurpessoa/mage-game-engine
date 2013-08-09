#include "Core.hpp"
#include "Character.hpp"
#include "GameObject.hpp"

class OgreCharacter : public Character, public GameObject {
protected:
	Ogre::String mName;

	// Methods ---------------------------------------------------------------------------------
protected:
public:
	OgreCharacter (Ogre::String name, Ogre::SceneManager *sceneMgr) {
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
	~OgreCharacter () {
		mMainNode->detachAllObjects ();
		delete mEntity;
		mMainNode->removeAndDestroyAllChildren ();
		mSceneMgr->destroySceneNode (mName);
	}

	void update (Ogre::Real elapsedTime, OIS::Keyboard *input) {
		// Handle movement
		if (input->isKeyDown (OIS::KC_W)) {
			mMainNode->translate (mMainNode->getOrientation () * Ogre::Vector3 (0, 0, 100 * elapsedTime));
		}
		if (input->isKeyDown (OIS::KC_S)) {
			mMainNode->translate (mMainNode->getOrientation () * Ogre::Vector3 (0, 0, -50 * elapsedTime));
		}
		if (input->isKeyDown (OIS::KC_A)) {
			mMainNode->yaw (Ogre::Radian (2 * elapsedTime));
		}
		if (input->isKeyDown (OIS::KC_D)) {
			mMainNode->yaw (Ogre::Radian (-2 * elapsedTime));
		}
	}

	// Change visibility - Useful for 1st person view ;)
	void setVisible (bool visible) {
		mMainNode->setVisible (visible);
	}
};