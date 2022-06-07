#include "Entity/Entity.h"
#include "Scene/GameScene.h"

/*���캯�� ��������*/
Entity::Entity()
{
	_isPlayer = false;
	_isAI = false;
	_sprite = nullptr;
	_hpBar = nullptr;
	_hpBarLabel = nullptr;
	_isAttackAvailable = true;
}

Entity::~Entity()
{}

/*�󶨾���*/
void Entity::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	addChild(_sprite);
}

/*����Ѫ���ٷֱ�*/
void Entity::setHpBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getHpBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"),
		Rect(0, 0, _hpBarSize.width * percent, _hpBarSize.height)));
}

/*��ʼ��Ѫ��*/
void Entity::initHpBar(Entity* target)
{
	//Ѫ��
	auto hpBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"));
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setScale(0.5, 0.4);
	hpBar->setPosition(Vec2(-50, 55));
	target->setHpBar(hpBar);
	target->addChild(hpBar);
	target->setHpBarSize(hpBar->getContentSize());
	//Ѫ������
	auto hpBarLabel = Label::createWithTTF(
		StringUtils::format("%d", target->getCurrentHealthPoint()).c_str(),
		"fonts/Marker Felt.ttf", 15);
	hpBarLabel->setPosition(Vec2(0, 55));
	target->setHpBarLabel(hpBarLabel);
	target->addChild(hpBarLabel);
}

/*�����˺�*/
bool Entity::takeDamage(INT32 damage)
{
	/*��ǰѪ��*/
	_currentHealthPoint -= damage;
	float percent = float(_currentHealthPoint) / _healthPoint;
	if (_currentHealthPoint <= 0)
	{
		die();
		return true;
	}

	/*Ѫ��*/
	setHpBarPercent(percent);

	/*Ѫ������*/
	getHpBarLabel()->setString(StringUtils::format("%d", _currentHealthPoint));

	/*�����˺�ֵ*/
	auto number = Label::createWithTTF(StringUtils::format("%d", damage).c_str(), "fonts/Marker Felt.ttf", 48);
	number->setPosition(Vec2(0, 50));
	if (_isPlayer)
		number->setColor(Color3B::RED);
	this->addChild(number);

	auto jump = JumpBy::create(1.0f, Vec2::ZERO, 50, 1);
	auto vanish = CallFunc::create([=]() {
		this->removeChild(number,true);
		number->setVisible(false);
	});

	auto sequence = Sequence::create(jump,vanish, nullptr);
	
	number->runAction(sequence);

	return false;
}

/*����*/
void Entity::die()
{
	this->removeFromParent();
	GameScene::getGameScene()->removeFromEntityVector(this);
}