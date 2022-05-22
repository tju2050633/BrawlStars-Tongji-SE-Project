#include "Entity/Entity.h"

/*构造函数 析构函数*/
Entity::Entity(): _sprite(nullptr),_hpBar(nullptr)
{}

Entity::~Entity()
{}

/*绑定精灵*/
void Entity::bindSprite(Sprite* sprite)
{
    _sprite = sprite;
    addChild(_sprite);
}

/*承受伤害*/
void Entity::takeDamage(INT32 damage)
{
    _healthPoint -= damage;
    if(_healthPoint <= 0)
    {
        die();
    }
}
