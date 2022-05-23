#include "Entity/Bullet.h"
#include "Entity/Brawler.h"

/*��ʼ��*/
bool Bullet::init()
{
	return true;
}

/*�󶨾���*/
void Bullet::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	addChild(_sprite);
}

/*��������*/
void Bullet::setAttributes(INT32 damage, INT32 speed, INT32 range, Brawler* launcher)
{
	setDamage(damage);
	setSpeed(speed);
	setRange(range);
	setLauncher(launcher);
}

/*���ݴ���Ƕȣ�����*/
void Bullet::launch(Vec2 direction)
{
	Vec2 currentPosition = this->getPosition();
	//////////////////////
}

/*��ײ����λ�����ô˺���*/
void Bullet::collide(Entity* target)
{
	target->takeDamage(_damage);
	this->removeFromParent();
}