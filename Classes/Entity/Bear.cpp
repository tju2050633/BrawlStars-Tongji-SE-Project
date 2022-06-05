#include "Entity/Bear.h"
#include "Constant/Const.h"

bool Bear::init()
{
	if (!Entity::init())
	{
		return false;
	}

	_currentHealthPoint = BEAR_HP;
	_healthPoint = BEAR_HP;
	_attackDamage = BEAR_AD;
	_moveSpeed = BEAR_MS;
	_attackInterval = BEAR_AI;

	this->scheduleUpdate();

	return true;
}

void Bear::update(float dt)
{

}