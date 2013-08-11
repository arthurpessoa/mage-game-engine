#ifndef _GameState_hpp_
#define _GameState_hpp_

#include "Core.hpp"

class GameState;
class AppStateListener
{
public:
	AppStateListener(){};
	virtual ~AppStateListener(){};

	virtual void manageState(Ogre::String stateName, GameState* state) = 0;

	virtual GameState*	findByName(Ogre::String stateName) = 0;
	virtual void		changeState(GameState *state) = 0;
	virtual bool		pushState(GameState* state) = 0;
	virtual void		popAppState() = 0;
	virtual void		pauseState() = 0;
	virtual void		shutdown() = 0;
    virtual void        popAllAndPushState(GameState* state) = 0;
};

class GameState : public OIS::KeyListener, public OIS::MouseListener, public OgreBites::SdkTrayListener
{
public:
	static void create(AppStateListener* parent, const Ogre::String name){};

	void destroy(){delete this;}

	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual bool pause(){return true;}
	virtual void resume(){};
	virtual void update(double timeSinceLastFrame) = 0;
protected:
	GameState(){};

	GameState*	findByName(Ogre::String stateName){return mParent->findByName(stateName);}
	void		changeAppState(GameState* state){mParent->changeState(state);}
	bool		pushAppState(GameState* state){return mParent->pushState(state);}
	void		popAppState(){mParent->popAppState();}
	void		shutdown(){mParent->shutdown();}
    void        popAllAndPushAppState(GameState* state){mParent->popAllAndPushState(state);}

	AppStateListener*			mParent;
	Ogre::Camera*				mCamera;
	Ogre::SceneManager*			mSceneManager;
    Ogre::FrameEvent            m_FrameEvent;
};

#define DECLARE_STATE(T)										\
static void create(AppStateListener* parent, const Ogre::String name)	\
{																		\
	T* myState = new T();											\
	myState->mParent = parent;										\
	parent->manageState(name, myState);							\
}

#endif