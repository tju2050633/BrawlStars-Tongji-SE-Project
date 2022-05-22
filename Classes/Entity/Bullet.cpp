#include "Entity/Entity.h"
#include "Entity/Bullet.h"
#include "Entity/Brawler.h"

/*构造函数*/
Bullet::Bullet() : _launcher(nullptr), _range(0)
{}

/*初始化*/
bool Bullet::init()
{
	/*初始化父类*/
	if (!Entity::init())
	{
		return false;
	}

	/*设置属性*/
	_healthPoint = 0;
	_attackInterval = 0;
	_inBush = false;

	return true;
}

/*自定义属性*/
void Bullet::setAttributes(INT32 attackDamage, INT32 moveSpeed, float range, Brawler* launcher)
{
	setAttackDamage(attackDamage);
	setMoveSpeed(moveSpeed);
	setRange(range);
	setLauncher(launcher);
}

/*根据传入角度，发射*/
void Bullet::launch(Vec2 direction)
{
	Vec2 currentPosition = this->getPosition();
	//////////////////////
}

/*碰撞到单位，调用此函数*/
void Bullet::collide(Entity* target)
{
	target->takeDamage(_attackDamage);
	this->removeFromParent();
}