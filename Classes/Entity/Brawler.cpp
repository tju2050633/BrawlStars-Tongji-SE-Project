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
	/*遍历已发射子弹，每帧进行移动*/
	for (auto bullet : _bulletVector)
	{
		float angle = bullet->getAngle();					//子弹角度
		float dx = (bullet->getSpeed() * cos(angle) - _moveSpeedX) * dt;	//子弹每帧移动量
		float dy = (bullet->getSpeed() * sin(angle) - _moveSpeedY) * dt;
		
		bullet->setPosition(bullet->getPosition() + Vec2(dx, dy));
	}
}

/*死亡*/
void Brawler::die()
{
	/*英雄数-1，配合GameScene的update刷新Label内容和出毒圈、换BGM、判定胜利等*/
	SceneUtils::_brawlerNumber--;
}

/*获得buff，增加属性*/
void Brawler::takeBuff()
{
	_healthPoint += 400;

	//加攻击力...
}