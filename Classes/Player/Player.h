#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

class Player {
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //²Ù×ÝµÄÓ¢ÐÛ
};

#endif // !__PLAYER_H_
