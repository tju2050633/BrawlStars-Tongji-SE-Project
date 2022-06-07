#include <cmath>
#include "Brawler/Stu.h"
#include "Constant/Const.h"
#include "Utils/SceneUtils.h"
#include "Utils/MusicUtils.h"

bool Stu::init()

{
	if (!Brawler::init())
	{
		return false;
	}
	_attackDamage = STU_AD;
	_currentHealthPoint = STU_HP;
	_healthPoint = STU_HP;
	_maxEnergy = STU_EB;
	_moveSpeed = STU_MS;
	_animateBrawler = AnimationUtils::Stu;
	return true;
}

void Stu::attack(float angle)
{
	if (_ammo <= 0 || !_isAttackAvailable)
		return;

	/*调用父类函数*/
	Brawler::attack(angle);

	/*一定触发攻击音效*/
	if (_isPlayer)
		MusicUtils::playEffect("Music/Stu/Stu_Attack.mp3");


	/*设定攻击间隔时间后才能下一次攻击*/
	_isAttackAvailable = false;
	scheduleOnce([&](float dt) {
		_isAttackAvailable = true;
		}, STU_AI, "resumeAttack");

	/*Stu攻击：射出2颗子弹*/
	schedule([=](float dt) {
		auto bullet = Bullet::create();
		//属性
		bullet->setLauncher(this);
		bullet->setDamage(_attackDamage);
		bullet->setRange(STU_BULLET_RANGE);
		bullet->setSpeed(STU_BULLET_SPEED);
		bullet->setAngle(angle);
		//图片
		auto sprite = Sprite::createWithTexture(
			Director::getInstance()->getTextureCache()
			->addImage("Animation/Stu_Bullet.png"));
		sprite->setRotation(-angle * 180 / M_PI);
		bullet->bindSprite(sprite);

		bullet->setIsAbility(false);
		this->addChild(bullet);
		_bulletVector.pushBack(bullet);
		}, 0.15, 1, 0, "stuAttack");
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
	if (_isPlayer && CCRANDOM_0_1() < 0.5f)
		MusicUtils::playEffect("Music/Stu/Stu_Ult.mp3");


	/*斯图技能：突刺*/

	float duration = 0.3f;
	_isCastingAbility = true;
	INT32 originMS_X = _moveSpeedX;
	INT32 originMS_Y = _moveSpeedY;
	_moveSpeedX = STU_DASH_DITANCE / duration * cos(angle);
	_moveSpeedY = STU_DASH_DITANCE / duration * sin(angle);
	scheduleOnce([=](float dt) {
		if (_keysReleased)
		{
			_moveSpeedX = 0;
			_moveSpeedY = 0;
		}
		else
		{
			_moveSpeedX = originMS_X;
			_moveSpeedY = originMS_Y;
		}

		_isCastingAbility = false;
		}, duration, "finishAbility");
}

bool Stu::takeDamage(INT32 damage)
{
	if (Brawler::takeDamage(damage))
		return true;

	/*受伤音效*/
	if (_isPlayer && CCRANDOM_0_1() < 0.5f)
		MusicUtils::playEffect("Music/Stu/Stu_Hurt.mp3");


	return false;
}

void Stu::die()
{
	/*调用父类函数*/
	Brawler::die();

	/*死亡音效*/
	MusicUtils::playEffect("Music/Stu/Stu_Die.mp3");
}