#include "Entity/Entity.h"

/*���캯��*/
Bullet(): _launcher(nullptr)
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
	healthPoint = 0;
	attackInterval = 0;
	inBush = false;

    return true;
}   

/*�Զ�������*/
void setAttributes(INT32 attackDamage, INT32 moveSpeed, float range, Brawler* launcher)
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