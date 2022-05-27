#include "Entity/Entity.h"

/*���캯�� ��������*/
Entity::Entity() : _sprite(nullptr), _hpBar(nullptr)
{}

Entity::~Entity()
{}

/*�󶨾���*/
void Entity::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	addChild(_sprite);

	/*���������ʵ����ײ���λ��*/
	Size size = _sprite->getContentSize();
	_sprite->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
	this->setContentSize(size);
}

/*��Ѫ��*/
void Entity::bindHpBar(Sprite* hpBar)
{
	_hpBar = hpBar;
	addChild(_hpBar);
}

/*�����˺�*/
void Entity::takeDamage(INT32 damage)
{
	_healthPoint -= damage;
	if (_healthPoint <= 0)
	{
		die();
	}
}