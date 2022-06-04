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

	/*调用父类函数*/
	Brawler::attack(angle);

	auto bullet = Bullet::create();
	/*绑定精灵图像，添加为子节点*/
	bullet->setSprite(Sprite::create("bullet.png"));
	bullet->addChild(bullet->getSprite());
	
	/*设置尺寸、角度及属性*/
	bullet->getSprite()->setScale(0.02);
	bullet->setRotation(90 - angle * 180 / M_PI);
	bullet->setAttributes(SHELLY_AD, SHELLY_BULLET_SPEED, SHELLY_BULLET_RANGE, angle, this);

	_bulletVector.pushBack(bullet);
	this->addChild(bullet);

	/*一定概率触发攻击音效*/
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Attack.mp3");
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
		SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Ult.mp3");

	
}

void Shelly::takeDamage(INT32 damage)
{
	/*调用父类函数*/
	Brawler::takeDamage(damage);

	/*受伤音效*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Hurt.mp3");
}

void Shelly::die()
{
	/*调用父类函数*/
	Brawler::die();

	/*死亡音效*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Shelly/Shelly_Die.mp3");
}