#include "Entity/Entity.h"

/*构造函数 析构函数*/
Entity::Entity() : _sprite(nullptr), _hpBar(nullptr), _hpBarLabel(nullptr)
{}

Entity::~Entity()
{}

/*设置血条百分比*/
void Entity::setHpBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getHpBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"),
		Rect(0, 0, _hpBarSize.width * percent, _hpBarSize.height)));
}

/*承受伤害*/
void Entity::takeDamage(INT32 damage)
{
	/*当前血量*/
	_currentHealthPoint -= damage;
	float percent = float(_currentHealthPoint) / _healthPoint;
	if (_currentHealthPoint <= 0)
	{
		die();
		_currentHealthPoint = 0;
		percent = 0;
	}

	/*血条*/
	setHpBarPercent(percent);

	/*血条文字*/
	getHpBarLabel()->setString(StringUtils::format("%d", _currentHealthPoint));
}
