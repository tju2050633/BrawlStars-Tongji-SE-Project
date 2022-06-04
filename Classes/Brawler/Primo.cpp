#include <cmath>
#include "Brawler/Primo.h"
#include "Constant/Const.h"

bool Primo::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	_currentHealthPoint = PRIMO_HP;
	_healthPoint = PRIMO_HP;
	_maxEnergy = PRIMO_EB;
	_moveSpeed = PRIMO_MS;
	_animateBrawler = AnimationUtils::Primo;
	return true;
}

void Primo::attack(float angle)
{
	if (_ammo <= 0)
		return;

	/*调用父类函数*/
	Brawler::attack(angle);

	/*一定概率触发攻击音效*/
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Attack.mp3");
}

void Primo::castAbility(float angle)
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
		SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Ult.mp3");
}

void Primo::takeDamage(INT32 damage)
{
	/*调用父类函数*/
	Brawler::takeDamage(damage);

	/*受伤音效*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Hurt.mp3");
}

void Primo::die()
{
	/*调用父类函数*/
	Brawler::die();

	/*死亡音效*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Die.mp3");
}