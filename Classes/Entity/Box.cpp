#include "Entity/Box.h"
#include "Constant/Const.h"

/*��ʼ��*/
bool Box::init()
{
	_healthPoint = BOX_HP;
	_attackDamage = 0;
	_moveSpeed = 0;
	_attackInterval = 0;

	return true;
}

/*�����飬����buff*/
void Box::die()
{

}