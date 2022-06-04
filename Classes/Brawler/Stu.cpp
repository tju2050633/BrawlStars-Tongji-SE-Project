#include <cmath>
#include "Brawler/Stu.h"
#include "Constant/Const.h"

bool Stu::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	_currentHealthPoint = STU_HP;
	_healthPoint = STU_HP;
	_maxEnergy = STU_EB;
	_moveSpeed = STU_MS;
	_animateBrawler = AnimationUtils::Stu;
	return true;
}

void Stu::attack(float angle)
{
	if (_ammo <= 0)
		return;

	/*���ø��ຯ��*/
	Brawler::attack(angle);

	/*һ������������Ч*/
	if(_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Attack.mp3");
}

void Stu::castAbility(float angle)
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
		SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Ult.mp3");

	/*˹ͼ���ܣ�ͻ��*/
	INT32 distance = 50;
	auto dash = MoveBy::create(1.0f, Vec2(distance * cos(angle), distance * sin(angle)));
	//this->runAction(dash);
}

void Stu::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	Brawler::takeDamage(damage);

	/*������Ч*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Hurt.mp3");
}

void Stu::die()
{
	/*���ø��ຯ��*/
	Brawler::die();

	/*������Ч*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Die.mp3");
}