#include "Object/Bullet.h"

/*create()模板*/
Bullet* Bullet::create(const std::string& filename, Brawler* launcher, INT32 damage, float range, float speed)
{
    Bullet* bullet = new (std::nothrow) Bullet();
	if (bullet && bullet->init(filename, launcher, damage, range, speed))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

/*初始化*/
bool Bullet::init(const std::string& filename, Brawler* launcher, INT32 damage, float range, float speed)
{
    /*初始化父类*/
    if (!Sprite::initWithFile(filename))
	{
		return false;
	}

    /*初始化成员变量*/
    _launcher = launcher;
    _damage = damage;

    return true;
}   

/*根据传入角度，发射*/
void Bullet::launch(float angle)
{

}

/*碰撞到单位，调用此函数*/
void Bullet::collide(Unit* target)
{

}