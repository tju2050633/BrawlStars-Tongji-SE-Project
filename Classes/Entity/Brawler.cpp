#include "cocos2d.h"
#include "Entity/Brawler.h"

bool Brawler::init()
{
	return true;
}

/*�ƶ�*/
void Brawler::move()
{

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