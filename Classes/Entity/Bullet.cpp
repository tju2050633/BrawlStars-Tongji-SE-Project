#include "Entity/Bullet.h"
#include "Entity/Brawler.h"

/*初始化*/
bool Bullet::init()
{
	return true;
}

/*绑定精灵*/
void Bullet::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	addChild(_sprite);
}

/*设置属性*/
void Bullet::setAttributes(INT32 damage, INT32 speed, INT32 range, float angle, Brawler* launcher)
{
	setDamage(damage);
	setSpeed(speed);
	setRange(range);
	setAngle(angle);
	setLauncher(launcher);
}

/*碰撞到单位，调用此函数*/
void Bullet::collide(Entity* target)
{
	target->takeDamage(_damage);
	this->removeFromParent();
}