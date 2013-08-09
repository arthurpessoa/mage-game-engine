#include "Core.hpp"

class ExtendedCamera {
protected:
	Ogre::SceneNode *mTargetNode; // The camera target
	Ogre::SceneNode *mCameraNode; // The camera itself
	Ogre::Camera *mCamera; // Ogre camera
	Ogre::SceneManager *mSceneMgr;
	Ogre::String mName;
	Ogre::Real mTightness; // Determines the movement of the camera - 1 means tight movement, while 0 means no movement
	bool mOwnCamera; // To know if the ogre camera binded has been created outside or inside of this class	

public:
	ExtendedCamera (Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::Camera *camera = 0);
	~ExtendedCamera ();
	void setTightness(Ogre::Real tightness);
	Ogre::Real getTightness ();
	Ogre::Vector3 getCameraPosition ();
	void instantUpdate (Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition);
	void update (Ogre::Real elapsedTime, Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition);
};