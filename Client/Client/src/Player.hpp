#include "Core.hpp"
#include "Character.hpp"
#include "GameObject.hpp"

class Player : public Character, public GameObject {
public:
	Player(Ogre::String name, Ogre::SceneManager *sceneMgr);
	~Player();
	void update (Ogre::Real elapsedTime);
	// Change visibility - Useful for 1st person view ;)
	void setVisible (bool visible);
};