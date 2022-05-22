#include "Entity/Entity.h"
#include "Entity/Bullet.h"
#include "Entity/Brawler.h"

/*���캯��*/
Bullet::Bullet() : _launcher(nullptr), _range(0)
{}

/*��ʼ��*/
bool Bullet::init()
{
	/*��ʼ������*/
	if (!Entity::init())
	{
		return false;
	}

	/*��������*/
	_healthPoint = 0;
	_attackInterval = 0;
	_inBush = false;

	return true;
}

/*�Զ�������*/
void Bullet::setAttributes(INT32 attackDamage, INT32 moveSpeed, float range, Brawler* launcher)
{
	setAttackDamage(attackDamage);
	setMoveSpeed(moveSpeed);
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
	target->takeDamage(_attackDamage);
	this->removeFromParent();
}