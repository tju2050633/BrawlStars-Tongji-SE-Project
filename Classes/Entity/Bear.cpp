#include "Entity/Bear.h"
#include "Constant/Const.h"
#include "Scene/GameScene.h"

bool Bear::init()
{
	//���Գ�ʼ��
	_currentHealthPoint = _healthPoint = BEAR_HP;
	_attackDamage = BEAR_AD;
	_moveSpeed = BEAR_MS;
	_attackInterval = BEAR_AI;

	//��ӽ�GameScene������
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