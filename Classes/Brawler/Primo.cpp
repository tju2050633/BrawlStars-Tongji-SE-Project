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

	/*���ø��ຯ��*/
	Brawler::attack(angle);

	/*һ�����ʴ���������Ч*/
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Attack.mp3");
}

void Primo::castAbility(float angle)
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
		SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Ult.mp3");
}

void Primo::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	Brawler::takeDamage(damage);

	/*������Ч*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Hurt.mp3");
}

void Primo::die()
{
	/*���ø��ຯ��*/
	Brawler::die();

	/*������Ч*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Primo/Primo_Die.mp3");
}