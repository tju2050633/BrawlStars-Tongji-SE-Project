#include <cmath>
#include "Brawler/Nita.h"
#include "Constant/Const.h"

bool Nita::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	_currentHealthPoint = NITA_HP;
	_healthPoint = NITA_HP;
	_maxEnergy = NITA_EB;
	_moveSpeed = NITA_MS;
	_animateBrawler = AnimationUtils::Nita;
	return true;
}

void Nita::attack(float angle)
{
	if (_ammo <= 0)
		return;

	/*调用父类函数*/
	Brawler::attack(angle);

	/*一定概率触发攻击音效*/
	if(_isPlayer && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Attack.mp3");
}

void Nita::castAbility(float angle)
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
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Ult.mp3");
}

void Nita::takeDamage(INT32 damage)
{
	/*调用父类函数*/
	Brawler::takeDamage(damage);

	/*受伤音效*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Hurt.mp3");
}

void Nita::die()
{
	/*调用父类函数*/
	Brawler::die();

	/*死亡音效*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Die.mp3");
}