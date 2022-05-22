#include "Entity/Entity.h"

/*���캯�� ��������*/
Entity::Entity(): _sprite(nullptr),_hpBar(nullptr)
{}

Entity::~Entity()
{}

/*�󶨾���*/
void Entity::bindSprite(Sprite* sprite)
{
    _sprite = sprite;
    addChild(_sprite);
}

/*�����˺�*/
void Entity::takeDamage(INT32 damage)
{
    _healthPoint -= damage;
    if(_healthPoint <= 0)
    {
        die();
    }
}
