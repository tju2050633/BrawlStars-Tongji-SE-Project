#include "cocos2d.h"
#include "Entity/Brawler.h"

bool Brawler::init()
{
	_ammo = 3;
	_energyBar = 0;
	return true;
}

/*����*/
void Brawler::die()
{

}

/*���buff����������*/
void Brawler::takeBuff()
{
	_healthPoint += 400;

	//�ӹ�����...
}