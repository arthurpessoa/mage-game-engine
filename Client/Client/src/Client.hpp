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

#ifndef _Game_hpp_
#define _Game_hpp_

#include "Core.hpp"
#include "GameState\GameStateManager.hpp"

class Client
{
public:
	Client();
	~Client();

	void start();

private:
	GameStateManager*	mAppStateManager;
};

#endif