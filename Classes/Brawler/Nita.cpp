#include <cmath>
#include "Brawler/Nita.h"
#include "Constant/Const.h"
#include "Utils/SceneUtils.h"
#include "Utils/AnimationUtils.h"
#include "Scene/GameScene.h"

bool Nita::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	_attackDamage = NITA_AD;
	_currentHealthPoint = NITA_HP;
	_healthPoint = NITA_HP;
	_maxEnergy = NITA_EB;
	_moveSpeed = NITA_MS;
	_animateBrawler = AnimationUtils::Nita;
	return true;
}

void Nita::attack(float angle)
{
	if (_ammo <= 0 || !_isAttackAvailable)
		return;

	/*调用父类函数*/
	Brawler::attack(angle);

	/*一定概率触发攻击音效*/
	if(_isPlayer && SceneUtils::_effectOn && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Attack.mp3");

	/*设定攻击间隔时间后才能下一次攻击*/
	_isAttackAvailable = false;
	scheduleOnce([&](float dt) {
		_isAttackAvailable = true;
		}, NITA_AI, "resumeAttack");

	/*Nita攻击：射出1道波*/
	auto bullet = Bullet::create();
	//属性
	bullet->setLauncher(this);
	bullet->setDamage(_attackDamage);
	bullet->setRange(NITA_BULLET_RANGE);
	bullet->setSpeed(NITA_BULLET_SPEED);
	bullet->setAngle(angle);
	//图片
	auto sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Animation/Nita_Bullet.png"));
	sprite->setScale(0.5);
	bullet->bindSprite(sprite);

	bullet->setIsAbility(false);
	this->addChild(bullet);
	_bulletVector.pushBack(bullet);

	//test
	if (_bear)
	{
		if (angle >= -M_PI / 4 && angle <= M_PI / 4)
			AnimationUtils::runAnimate(_bear, AnimationUtils::bear, AnimationUtils::Right, 1, 3, -1);
		else if (angle >= M_PI / 4 && angle <= 3 * M_PI / 4)
			AnimationUtils::runAnimate(_bear, AnimationUtils::bear, AnimationUtils::Top, 1, 3, -1);
		else if (angle >= 3 * M_PI / 4 && angle <= 5 * M_PI / 4)
			AnimationUtils::runAnimate(_bear, AnimationUtils::bear, AnimationUtils::Left, 1, 3, -1);
		else if (angle >= 5 * M_PI / 4 || angle <= -M_PI / 4)
			AnimationUtils::runAnimate(_bear, AnimationUtils::bear, AnimationUtils::Bottom, 1, 3, -1);
	}
}

void Nita::castAbility(float angle)
{
	//确保熊的出生点不会出界
	auto deltaPosition = Vec2(NITA_ABILITY_RANGE * cos(angle), NITA_ABILITY_RANGE * sin(angle));
	auto pos = GameScene::getGameScene()->tileCoordForPosition(deltaPosition + getParent()->getPosition());
	if (!(pos.x < 47 && pos.y < 37 && pos.x >= 3 && pos.y >= 3))
		return;

	/*能量未满，无反应；释放成功，则能量清零*/
	if (_energy != _maxEnergy)
		return;
	_energy = 0;
	setEnergeBarPercent(0);

	/*调用父类函数*/
	Brawler::castAbility(angle);

	/*技能音效*/
	if (_isPlayer && SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Ult.mp3");

	/*Nita技能：召唤一只熊*/
	if (_bear != nullptr)
		_bear->removeFromParent();//移除旧熊

	auto bear = Bear::create();
	bear->setPosition(getParent()->getPosition() + deltaPosition);
	bear->bindSprite(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bear_Bottom1.png")));

	//绑定关系，但熊不是英雄的子节点
	_bear = bear;
	_bear->setOwner(this);
	this->getParent()->getParent()->addChild(_bear,1);

	//播放降落动画
	AnimationUtils::runAnimate(bear, AnimationUtils::Nita, AnimationUtils::boom, 0.5, 4, 1);

	//图片
	scheduleOnce([=](float dt) {
		AnimationUtils::stopAnimate(bear, AnimationUtils::bear, AnimationUtils::Bottom);
	}, 0.5, "bear");

	//血条
	Entity::initHpBar(_bear);
	
}

void Nita::takeDamage(INT32 damage)
{
	/*调用父类函数*/
	Brawler::takeDamage(damage);

	/*受伤音效*/
	if (_isPlayer && SceneUtils::_effectOn && CCRANDOM_0_1() < 0.5f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Hurt.mp3");

	//test
	if (_bear)
	{
		AnimationUtils::runAnimate(_bear, AnimationUtils::bear, AnimationUtils::Attack, 0.5, 2, -1);
		_bear->takeDamage(damage);
	}
}

void Nita::die()
{
	/*调用父类函数*/
	Brawler::die();

	/*死亡音效*/
	if(SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Die.mp3");
}