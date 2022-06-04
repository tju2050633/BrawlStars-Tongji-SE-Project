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
	_currentHealthPoint = SHELLY_HP;
	_healthPoint = SHELLY_HP;
	_maxEnergy = SHELLY_EB;
	_moveSpeed = SHELLY_MS;
	_animateBrawler = AnimationUtils::Shelly;
	return true;
}

void Shelly::attack(float angle)
{
	if (_ammo <= 0)
		return;

	/*���ø��ຯ��*/
	Brawler::attack(angle);

	auto bullet = Bullet::create();
	/*�󶨾���ͼ�����Ϊ�ӽڵ�*/
	bullet->setSprite(Sprite::create("bullet.png"));
	bullet->addChild(bullet->getSprite());
	
	/*���óߴ硢�Ƕȼ�����*/
	bullet->getSprite()->setScale(0.02);
	bullet->setRotation(90 - angle * 180 / M_PI);
	bullet->setAttributes(SHELLY_AD, SHELLY_BULLET_SPEED, SHELLY_BULLET_RANGE, angle, this);

	_bulletVector.pushBack(bullet);
	this->addChild(bullet);

	/*һ�����ʴ���������Ч*/
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Attack.mp3");
}

void Shelly::castAbility(float angle)
{
	/*����δ�����޷�Ӧ���ͷųɹ�������������*/
	if (_energy != _maxEnergy)
		return;
	_energy = 0;
	setEnergeBarPercent(0);

	/*���ø��ຯ��*/
	Brawler::castAbility(angle);

	/*������Ч*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Ult.mp3");

	
}

void Shelly::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	Brawler::takeDamage(damage);

	/*������Ч*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Hurt.mp3");
}

void Shelly::die()
{
	/*���ø��ຯ��*/
	Brawler::die();

	/*������Ч*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Die.mp3");
}