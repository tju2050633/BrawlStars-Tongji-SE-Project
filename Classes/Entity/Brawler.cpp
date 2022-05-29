#include "cocos2d.h"
#include "Entity/Brawler.h"

bool Brawler::init()
{
	_ammo = 3;
	_energyBar = 0;
	return true;
}

/*死亡*/
void Brawler::die()
{

}

/*获得buff，增加属性*/
void Brawler::takeBuff()
{
	_healthPoint += 400;

	//加攻击力...
}