#include "Entity/Box.h"
#include "Constant/Const.h"

/*初始化*/
bool Box::init()
{
	_healthPoint = BOX_HP;
	_attackDamage = 0;
	_moveSpeed = 0;
	_attackInterval = 0;

	return true;
}

/*被打碎，掉落buff*/
void Box::die()
{

}