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

	/*调用父类函数*/
	Brawler::attack(angle);

	/*一定触发攻击音效*/
	if(_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Attack.mp3");
}

void Stu::castAbility(float angle)
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
		SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Ult.mp3");

	/*斯图技能：突刺*/
	INT32 distance = 50;
	auto dash = MoveBy::create(1.0f, Vec2(distance * cos(angle), distance * sin(angle)));
	//this->runAction(dash);
}

void Stu::takeDamage(INT32 damage)
{
	/*调用父类函数*/
	Brawler::takeDamage(damage);

	/*受伤音效*/
	if (_isPlayer)
		SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Hurt.mp3");
}

void Stu::die()
{
	/*调用父类函数*/
	Brawler::die();

	/*死亡音效*/
	SimpleAudioEngine::getInstance()->playEffect("Music/Stu/Stu_Die.mp3");
}