#include "Entity/Entity.h"

/*构造函数 析构函数*/
Entity::Entity() : _sprite(nullptr), _hpBar(nullptr)
{}

Entity::~Entity()
{}

/*绑定精灵*/
void Entity::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	addChild(_sprite);

	/*调整精灵和实体碰撞体积位置*/
	Size size = _sprite->getContentSize();
	_sprite->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
	this->setContentSize(size);
}

/*绑定血条*/
void Entity::bindHpBar(Sprite* hpBar)
{
	_hpBar = hpBar;
	addChild(_hpBar);
}

/*承受伤害*/
void Entity::takeDamage(INT32 damage)
{
	_healthPoint -= damage;
	if (_healthPoint <= 0)
	{
		die();
	}
}