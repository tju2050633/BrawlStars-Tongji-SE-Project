#include "Entity/Entity.h"
#include "Scene/GameScene.h"

/*构造函数 析构函数*/
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

/*绑定精灵*/
void Entity::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	addChild(_sprite);
}

/*设置血条百分比*/
void Entity::setHpBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getHpBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"),
		Rect(0, 0, _hpBarSize.width * percent, _hpBarSize.height)));
}

/*初始化血条*/
void Entity::initHpBar(Entity* target)
{
	//血条
	auto hpBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"));
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setScale(0.5, 0.4);
	hpBar->setPosition(Vec2(-50, 55));
	target->setHpBar(hpBar);
	target->addChild(hpBar);
	target->setHpBarSize(hpBar->getContentSize());
	//血条文字
	auto hpBarLabel = Label::createWithTTF(
		StringUtils::format("%d", target->getCurrentHealthPoint()).c_str(),
		"fonts/Marker Felt.ttf", 15);
	hpBarLabel->setPosition(Vec2(0, 55));
	target->setHpBarLabel(hpBarLabel);
	target->addChild(hpBarLabel);
}

/*承受伤害*/
bool Entity::takeDamage(INT32 damage)
{
	/*当前血量*/
	_currentHealthPoint -= damage;
	float percent = float(_currentHealthPoint) / _healthPoint;
	if (_currentHealthPoint <= 0)
	{
		die();
		return true;
	}

	/*血条*/
	setHpBarPercent(percent);

	/*血条文字*/
	getHpBarLabel()->setString(StringUtils::format("%d", _currentHealthPoint));

	/*跳出伤害值*/
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

/*死亡*/
void Entity::die()
{
	this->removeFromParent();
	GameScene::getGameScene()->removeFromEntityVector(this);
}