#include <cmath>
#include "Brawler/Primo.h"
#include "Constant/Const.h"
#include "Utils/SceneUtils.h"
#include "Utils/MusicUtils.h"
#include "Scene/GameScene.h"

bool Primo::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	_attackDamage = PRIMO_AD;
	_currentHealthPoint = PRIMO_HP;
	_healthPoint = PRIMO_HP;
	_maxEnergy = PRIMO_EB;
	_moveSpeed = PRIMO_MS;
	_animateBrawler = AnimationUtils::Primo;
	return true;
}

void Primo::attack(float angle)
{
	if (_ammo <= 0 || !_isAttackAvailable)
		return;

	/*���ø��ຯ��*/
	Brawler::attack(angle);

	/*һ�����ʴ���������Ч*/
	if (_isPlayer && CCRANDOM_0_1() < 0.3f)
		MusicUtils::playEffect("Music/Primo/Primo_Attack.mp3");

	/*�趨�������ʱ��������һ�ι���*/
	_isAttackAvailable = false;
	scheduleOnce([&](float dt) {
		_isAttackAvailable = true;
		}, PRIMO_AI, "resumeAttack");

	/*Primo���������4��ȭͷ����scheduleʵ����ʱ*/
	schedule([=](float dt) {
		static int iPrimoBulletNumber = 1;
		auto bullet = Bullet::create();
		//����
		bullet->setLauncher(this);
		bullet->setDamage(_attackDamage);
		bullet->setRange(PRIMO_BULLET_RANGE);
		bullet->setSpeed(PRIMO_BULLET_SPEED);
		bullet->setAngle(angle);
		//ͼƬ
		auto sprite = Sprite::createWithTexture(
			Director::getInstance()->getTextureCache()->
			addImage(StringUtils::format("Animation/Primo_Bullet%d.png", iPrimoBulletNumber)));
		iPrimoBulletNumber = iPrimoBulletNumber % 4 + 1;//1~4ѭ��
		sprite->setScale(0.3, 0.6);
		sprite->setAnchorPoint(Vec2(0.1, 0.5));
		sprite->setRotation(-angle * 180 / M_PI);
		bullet->bindSprite(sprite);
		bullet->setIsAbility(false);

		this->addChild(bullet);
		_bulletVector.pushBack(bullet);
		}, 0.1, 3, 0, "primoAttack");
}

void Primo::castAbility(float angle)
{
	//ȷ�����к󲻻����
	auto deltaPosition = Vec2(PRIMO_ABILITY_RANGE * cos(angle), PRIMO_ABILITY_RANGE * sin(angle));
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
		MusicUtils::playEffect("Music/Primo/Primo_Ult.mp3");

	/*Primo���ܣ��ɳ�һ�ξ��룬���Դݻ�ǽ��*/
	auto leap = MoveBy::create(1, deltaPosition);
	auto destroyWall = CallFunc::create([=]() {
		auto X = GameScene::getGameScene()->getTileSize().width;
		auto Y = GameScene::getGameScene()->getTileSize().height;
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition());
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(X, 0));
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(X, Y));
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(X, -Y));
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(0, Y));
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(0, -Y));
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(-X, Y));
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(-X, 0));
		GameScene::getGameScene()->breakWall(this->getParent()->getPosition() + Vec2(-X, -Y));
		});
	auto sequence = Sequence::create(leap, destroyWall, nullptr);
	this->getParent()->runAction(sequence);
}

bool Primo::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	if (Brawler::takeDamage(damage))
		return true;

	/*������Ч*/
	if (_isPlayer && CCRANDOM_0_1() < 0.5f)
		MusicUtils::playEffect("Music/Primo/Primo_Hurt.mp3");


	return false;
}

void Primo::die()
{
	/*���ø��ຯ��*/
	Brawler::die();

	/*������Ч*/
	MusicUtils::playEffect("Music/Primo/Primo_Die.mp3");

}