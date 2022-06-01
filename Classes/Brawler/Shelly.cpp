#include <cmath>
#include "Brawler/Shelly.h"
#include "Constant/Const.h"
#include "Entity/Bullet.h"

bool Shelly::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	setMoveSpeed(SHELLY_MS);
	return true;
}

void Shelly::attack(float angle)
{
	auto bullet = Bullet::create();
	/*绑定精灵图像，添加为子节点*/
	bullet->setSprite(Sprite::create("bullet.png"));
	bullet->addChild(bullet->getSprite());
	
	/*设置尺寸、角度及属性*/
	bullet->getSprite()->setScale(0.02);
	bullet->setRotation(90 - angle * 180 / M_PI);
	bullet->setAttributes(SHELLY_AD, SHELLY_BULLET_SPEED, SHELLY_BULLET_RANGE, angle, this);

	_bulletVector.pushBack(bullet);
	this->addChild(bullet);
}

void Shelly::castAbility(float angle)
{

}