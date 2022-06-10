#include <cmath>
#include "Brawler/Nita.h"
#include "Constant/Const.h"
#include "Utils/SceneUtils.h"
#include "Utils/MusicUtils.h"
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
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		MusicUtils::playEffect("Music/Nita/Nita_Attack.mp3");


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
	if (_isPlayer)
		MusicUtils::playEffect("Music/Nita/Nita_Ult.mp3");

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

bool Nita::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	if (Brawler::takeDamage(damage))
		return true;

	/*������Ч*/
	if (_isPlayer && CCRANDOM_0_1() < 0.5f)
		MusicUtils::playEffect("Music/Nita/Nita_Hurt.mp3");

	return false;
}

void Nita::die()
{
	/*���ø��ຯ��*/
	Brawler::die();

	/*������*/
	if(_bear != nullptr)
		_bear->die();

	/*������Ч*/
	MusicUtils::playEffect("Music/Nita/Nita_Die.mp3");
}