#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity : public Node {
	/*属性*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);          //精灵
	CC_SYNTHESIZE(Sprite*, _hpBar, HpBar);      //血条组件
	CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);  //血量
	CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);//攻击力
	CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);      //移速
	CC_SYNTHESIZE(float, _attackInterval, AttackInterval);  //攻击间隔
	CC_SYNTHESIZE(bool, _inBush, InBush);           //判断是否在草丛中
private:

public:
	/*构造函数 析构函数*/
	Entity();
	virtual ~Entity();

	/*绑定精灵*/
	void bindSprite(Sprite* sprite);
	/*绑定血条*/
	void bindHpBar(Sprite* hpBar);

	virtual void attack(float angle) {}  //攻击
	virtual void die() {}  //死亡
	void takeDamage(INT32 damage);  //承受伤害
};

#endif// !__ENTITY_H_