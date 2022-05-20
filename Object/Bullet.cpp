#include "Object/Bullet.h"

/*create()ģ��*/
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

/*��ʼ��*/
bool Bullet::init(const std::string& filename, Brawler* launcher, INT32 damage, float range, float speed)
{
    /*��ʼ������*/
    if (!Sprite::initWithFile(filename))
	{
		return false;
	}

    /*��ʼ����Ա����*/
    _launcher = launcher;
    _damage = damage;

    return true;
}   

/*���ݴ���Ƕȣ�����*/
void Bullet::launch(float angle)
{

}

/*��ײ����λ�����ô˺���*/
void Bullet::collide(Unit* target)
{

}