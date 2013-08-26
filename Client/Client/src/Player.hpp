#ifndef _Player_hpp_
#define _Player_hpp_

#include "Character.hpp"
#include "GameObject.hpp"

class Player : public Character, public GameObject {
public:
	Player(Ogre::String name, Ogre::SceneManager *sceneMgr);
	~Player();
	void update (Ogre::Real elapsedTime);
};

#endif