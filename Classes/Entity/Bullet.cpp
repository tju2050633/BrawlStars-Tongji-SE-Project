#include "Entity/Bullet.h"
#include "Entity/Brawler.h"

/*初始化*/
bool Bullet::init()
{
	_distance = 0;
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

/*碰撞英雄*/
void Bullet::collideWithBrawler(Brawler* target)
{
	this->removeFromParent();	//子弹移除
	_launcher->dealDamage(_damage);//发射者造成伤害

	if (target->takeDamage(_damage))//实体受伤,若击杀了目标
	{
		_launcher->kill(target);
	}
}

/*碰撞熊、宝箱*/
void Bullet::collideWithEntity(Entity* target)
{
	target->takeDamage(_damage);//实体受伤
	this->removeFromParent();	//子弹移除
	_launcher->dealDamage(_damage);//发射者造成伤害
}