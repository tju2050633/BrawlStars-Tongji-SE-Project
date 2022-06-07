#include <cmath>
#include "Brawler/Shelly.h"
#include "Constant/Const.h"
#include "Utils/SceneUtils.h"
#include "Utils/MusicUtils.h"

bool Shelly::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	_attackDamage = SHELLY_AD;
	_currentHealthPoint = SHELLY_HP;
	_healthPoint = SHELLY_HP;
	_maxEnergy = SHELLY_EB;
	_moveSpeed = SHELLY_MS;
	_animateBrawler = AnimationUtils::Shelly;
	return true;
}

void Shelly::attack(float angle)
{
	if (_ammo <= 0 || !_isAttackAvailable)
		return;

	/*���ø��ຯ��*/
	Brawler::attack(angle);

	/*һ�����ʴ���������Ч*/
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		MusicUtils::playEffect("Music/Shelly/Shelly_Attack.mp3");


	/*�趨�������ʱ��������һ�ι���*/
	_isAttackAvailable = false;
	scheduleOnce([&](float dt) {
		_isAttackAvailable = true;
		}, SHELLY_AI, "resumeAttack");

	/*Shelly���������5���ӵ���ÿ��4��*/
	for (int i = -2; i <= 2; i++)
	{
		auto bullet = Bullet::create();
		//����
		bullet->setLauncher(this);
		bullet->setDamage(_attackDamage);
		bullet->setRange(SHELLY_BULLET_RANGE);
		bullet->setSpeed(SHELLY_BULLET_SPEED);
		bullet->setAngle(angle + 5 * i * M_PI / 180);
		//����4���ӵ���ͼƬ
		for (int j = 0; j < 4; j++)
		{
			auto sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Animation/Shelly_Bullet.png"));
			Vec2 position;
			switch (j)
			{
				case 0:
					position = Vec2(-10, 0);
					break;
				case 1:
					position = Vec2(10, 0);
				case 2:
					position = Vec2(0, 10);
					break;
				case 3:
					position = Vec2(0, -10);
					break;
				default:
					break;
			}
			sprite->setPosition(position);
			sprite->setRotation(90 - angle * 180 / M_PI - 5 * i);
			bullet->bindSprite(sprite);
		}
		bullet->setIsAbility(false);
		this->addChild(bullet);
		_bulletVector.pushBack(bullet);
	}
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
		MusicUtils::playEffect("Music/Shelly/Shelly_Ult.mp3");

	/*Shelly���ܣ����9���ӵ���ÿ��4��*/
	for (int i = -4; i <= 4; i++)
	{
		auto bullet = Bullet::create();
		//����
		bullet->setLauncher(this);
		bullet->setDamage(_attackDamage);
		bullet->setRange(SHELLY_BULLET_RANGE * 1.5);
		bullet->setDistance(0);
		bullet->setSpeed(SHELLY_BULLET_SPEED * 1.5);
		bullet->setAngle(angle + 2.5 * i * M_PI / 180);
		//����4���ӵ���ͼƬ
		for (int j = 0; j < 4; j++)
		{
			auto sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Animation/Shelly_Bullet.png"));
			Vec2 position;
			switch (j)
			{
				case 0:
					position = Vec2(-10, 0);
					break;
				case 1:
					position = Vec2(10, 0);
				case 2:
					position = Vec2(0, 10);
					break;
				case 3:
					position = Vec2(0, -10);
					break;
				default:
					break;
			}
			sprite->setScale(1.2);
			sprite->setPosition(position);
			sprite->setRotation(90 - angle * 180 / M_PI - 2.5 * i);
			bullet->bindSprite(sprite);
		}
		bullet->setIsAbility(true);
		this->addChild(bullet);
		_bulletVector.pushBack(bullet);
	}
}

bool Shelly::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	if (Brawler::takeDamage(damage))
		return true;

	/*������Ч*/
	if (_isPlayer && CCRANDOM_0_1() < 0.5f)
		MusicUtils::playEffect("Music/Shelly/Shelly_Hurt.mp3");


	return false;
}

void Shelly::die()
{
	/*���ø��ຯ��*/
	Brawler::die();

	/*������Ч*/
	MusicUtils::playEffect("Music/Shelly/Shelly_Die.mp3");

}