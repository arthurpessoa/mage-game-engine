
#ifndef _GameStateManager_hpp_
#define _GameStateManager_hpp_

#include "GameState.hpp"

class GameStateManager : public AppStateListener
{
public:
	typedef struct
	{
		Ogre::String name;
 		GameState* state;
	} state_info;

	GameStateManager();
	~GameStateManager();

	void manageState(Ogre::String stateName, GameState* state);

	GameState* findByName(Ogre::String stateName);

	void start(GameState* state);
	void changeState(GameState* state);
	bool pushState(GameState* state);
	void popAppState();
	void pauseState();
	void shutdown();
    void popAllAndPushState(GameState* state);

protected:
	void init(GameState *state);

	std::vector<GameState*>		m_ActiveStateStack;
	std::vector<state_info>		m_States;
	bool						m_bShutdown;
};
#endif