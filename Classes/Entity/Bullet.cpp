#include "Entity/Bullet.h"
#include "Entity/Brawler.h"

/*��ʼ��*/
bool Bullet::init()
{
	_distance = 0;
	return true;
}

/*�󶨾���*/
void Bullet::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	addChild(_sprite);
}

/*��������*/
void Bullet::setAttributes(INT32 damage, INT32 speed, INT32 range, float angle, Brawler* launcher)
{
	setDamage(damage);
	setSpeed(speed);
	setRange(range);
	setAngle(angle);
	setLauncher(launcher);
}

/*��ײӢ��*/
void Bullet::collideWithBrawler(Brawler* target)
{
	this->removeFromParent();	//�ӵ��Ƴ�
	_launcher->dealDamage(_damage);//����������˺�

	if (target->takeDamage(_damage))//ʵ������,����ɱ��Ŀ��
	{
		_launcher->kill(target);
	}
}

/*��ײ�ܡ�����*/
void Bullet::collideWithEntity(Entity* target)
{
	target->takeDamage(_damage);//ʵ������
	this->removeFromParent();	//�ӵ��Ƴ�
	_launcher->dealDamage(_damage);//����������˺�
}