#include "cocos2d.h"
#include "Entity/Brawler.h"

bool Brawler::init()
{
	return true;
}

/*获得buff，增加属性*/
void Brawler::takeBuff()
{
	_healthPoint += 400;

	//加攻击力...
}