#include "Entity/Entity.h"

/*���캯�� ��������*/
Entity::Entity() : _sprite(nullptr), _hpBar(nullptr), _hpBarLabel(nullptr)
{}

Entity::~Entity()
{}

/*����Ѫ���ٷֱ�*/
void Entity::setHpBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getHpBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"),
		Rect(0, 0, _hpBarSize.width * percent, _hpBarSize.height)));
}

/*�����˺�*/
void Entity::takeDamage(INT32 damage)
{
	/*��ǰѪ��*/
	_currentHealthPoint -= damage;
	float percent = float(_currentHealthPoint) / _healthPoint;
	if (_currentHealthPoint <= 0)
	{
		die();
		_currentHealthPoint = 0;
		percent = 0;
	}

	/*Ѫ��*/
	setHpBarPercent(percent);

	/*Ѫ������*/
	getHpBarLabel()->setString(StringUtils::format("%d", _currentHealthPoint));
}
