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

	/*���ø��ຯ��*/
	Brawler::attack(angle);

	/*һ�����ʴ���������Ч*/
	if(_isPlayer && SceneUtils::_effectOn && CCRANDOM_0_1() < 0.3f)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Attack.mp3");

	/*�趨�������ʱ��������һ�ι���*/
	_isAttackAvailable = false;
	scheduleOnce([&](float dt) {
		_isAttackAvailable = true;
		}, NITA_AI, "resumeAttack");

	/*Nita���������1����*/
	auto bullet = Bullet::create();
	//����
	bullet->setLauncher(this);
	bullet->setDamage(_attackDamage);
	bullet->setRange(NITA_BULLET_RANGE);
	bullet->setSpeed(NITA_BULLET_SPEED);
	bullet->setAngle(angle);
	//ͼƬ
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
	//ȷ���ܵĳ����㲻�����
	auto deltaPosition = Vec2(NITA_ABILITY_RANGE * cos(angle), NITA_ABILITY_RANGE * sin(angle));
	auto pos = GameScene::getGameScene()->tileCoordForPosition(deltaPosition + getParent()->getPosition());
	if (!(pos.x < 47 && pos.y < 37 && pos.x >= 3 && pos.y >= 3))
		return;

	/*����δ�����޷�Ӧ���ͷųɹ�������������*/
	if (_energy != _maxEnergy)
		return;
	_energy = 0;
	setEnergeBarPercent(0);

	/*���ø��ຯ��*/
	Brawler::castAbility(angle);

	/*������Ч*/
	if (_isPlayer && SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Ult.mp3");

	/*Nita���ܣ��ٻ�һֻ��*/
	if (_bear != nullptr)
		_bear->removeFromParent();//�Ƴ�����

	auto bear = Bear::create();
	bear->setPosition(getParent()->getPosition() + deltaPosition);
	bear->bindSprite(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bear_Bottom1.png")));

	//�󶨹�ϵ�����ܲ���Ӣ�۵��ӽڵ�
	_bear = bear;
	_bear->setOwner(this);
	this->getParent()->getParent()->addChild(_bear,1);

	//���Ž��䶯��
	AnimationUtils::runAnimate(bear, AnimationUtils::Nita, AnimationUtils::boom, 0.5, 4, 1);

	//ͼƬ
	scheduleOnce([=](float dt) {
		AnimationUtils::stopAnimate(bear, AnimationUtils::bear, AnimationUtils::Bottom);
	}, 0.5, "bear");

	//Ѫ��
	Entity::initHpBar(_bear);
	
}

void Nita::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	Brawler::takeDamage(damage);

	/*������Ч*/
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
	/*���ø��ຯ��*/
	Brawler::die();

	/*������Ч*/
	if(SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/Nita/Nita_Die.mp3");
}