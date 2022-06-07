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

	/*调用父类函数*/
	Brawler::attack(angle);

	/*一定概率触发攻击音效*/
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		MusicUtils::playEffect("Music/Shelly/Shelly_Attack.mp3");


	/*设定攻击间隔时间后才能下一次攻击*/
	_isAttackAvailable = false;
	scheduleOnce([&](float dt) {
		_isAttackAvailable = true;
		}, SHELLY_AI, "resumeAttack");

	/*Shelly攻击：射出5簇子弹，每簇4颗*/
	for (int i = -2; i <= 2; i++)
	{
		auto bullet = Bullet::create();
		//属性
		bullet->setLauncher(this);
		bullet->setDamage(_attackDamage);
		bullet->setRange(SHELLY_BULLET_RANGE);
		bullet->setSpeed(SHELLY_BULLET_SPEED);
		bullet->setAngle(angle + 5 * i * M_PI / 180);
		//贴上4颗子弹的图片
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
	/*能量未满，无反应；释放成功，则能量清零*/
	if (_energy != _maxEnergy)
		return;
	_energy = 0;
	setEnergeBarPercent(0);

	/*调用父类函数*/
	Brawler::castAbility(angle);

	/*技能音效*/
	if (_isPlayer)
		MusicUtils::playEffect("Music/Shelly/Shelly_Ult.mp3");

	/*Shelly技能：射出9簇子弹，每簇4颗*/
	for (int i = -4; i <= 4; i++)
	{
		auto bullet = Bullet::create();
		//属性
		bullet->setLauncher(this);
		bullet->setDamage(_attackDamage);
		bullet->setRange(SHELLY_BULLET_RANGE * 1.5);
		bullet->setDistance(0);
		bullet->setSpeed(SHELLY_BULLET_SPEED * 1.5);
		bullet->setAngle(angle + 2.5 * i * M_PI / 180);
		//贴上4颗子弹的图片
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
	/*调用父类函数*/
	if (Brawler::takeDamage(damage))
		return true;

	/*受伤音效*/
	if (_isPlayer && CCRANDOM_0_1() < 0.5f)
		MusicUtils::playEffect("Music/Shelly/Shelly_Hurt.mp3");


	return false;
}

void Shelly::die()
{
	/*调用父类函数*/
	Brawler::die();

	/*死亡音效*/
	MusicUtils::playEffect("Music/Shelly/Shelly_Die.mp3");

}