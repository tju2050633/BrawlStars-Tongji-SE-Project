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

	/*���ø��ຯ��*/
	Brawler::attack(angle);

	/*һ�����ʴ���������Ч*/
	if(_isPlayer && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Attack.mp3");
}

void Nita::castAbility(float angle)
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
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Ult.mp3");
}

void Nita::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	Brawler::takeDamage(damage);

	/*������Ч*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Hurt.mp3");
}

void Nita::die()
{
	/*���ø��ຯ��*/
	Brawler::die();

	/*������Ч*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Die.mp3");
}