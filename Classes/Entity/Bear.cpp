#include "Entity/Bear.h"
#include "Constant/Const.h"
#include "Scene/GameScene.h"

bool Bear::init()
{
	//属性初始化
	_currentHealthPoint = _healthPoint = BEAR_HP;
	_attackDamage = BEAR_AD;
	_moveSpeed = BEAR_MS;
	_attackInterval = BEAR_AI;

	//添加进GameScene的数组
	GameScene::getGameScene()->pushBackEntity(this);

	this->scheduleUpdate();

	return true;
}

void Bear::update(float dt)
{

}

void Bear::die()
{
	Entity::die();
	_owner->setBear(nullptr);
}