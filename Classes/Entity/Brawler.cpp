#include <cmath>
#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Utils/SceneUtils.h"

bool Brawler::init()
{
	_ammo = 3;
	_energyBar = 0;
	_moveSpeedX = 0;
	_moveSpeedY = 0;

	this->scheduleUpdate();

	return true;
}

void Brawler::update(float dt)
{
	/*�����ѷ����ӵ���ÿ֡�����ƶ�*/
	for (auto bullet : _bulletVector)
	{
		float angle = bullet->getAngle();					//�ӵ��Ƕ�
		float dx = (bullet->getSpeed() * cos(angle) - _moveSpeedX) * dt;	//�ӵ�ÿ֡�ƶ���
		float dy = (bullet->getSpeed() * sin(angle) - _moveSpeedY) * dt;
		
		bullet->setPosition(bullet->getPosition() + Vec2(dx, dy));
	}
}

/*����*/
void Brawler::die()
{
	/*Ӣ����-1�����GameScene��updateˢ��Label���ݺͳ���Ȧ����BGM���ж�ʤ����*/
	SceneUtils::_brawlerNumber--;
}

/*���buff����������*/
void Brawler::takeBuff()
{
	_healthPoint += 400;

	//�ӹ�����...
}