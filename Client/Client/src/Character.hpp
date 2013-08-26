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


#ifndef _Character_hpp_
#define _Character_hpp_

#include "Core.hpp"

class Character{
protected:
	Ogre::String mName;
	short int mINT;
	short int mAGI;
	short int mSTR;
	short int mLUK;
	short int mDEX;

public:
	Ogre::String getName(){ return mName; }
};

#endif