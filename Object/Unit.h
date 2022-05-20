#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"

USING_NS_CC;

class Unit : public Sprite {
    /*属性*/
    CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);  //血量
    CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);//攻击力
    CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);      //移速
    CC_SYNTHESIZE(float, _attackInterval, AttackInterval);  //攻击间隔
    CC_SYNTHESIZE(bool, _inBush, InBush);           //判断是否在草丛中
    //血条组件
    //面向的方向
public:
    virtual void attack();  //攻击，没有实现
    void takeDamage(INT32 damage);  //承受伤害
    virtual void moveTo();  //移动，参数为目标地
    virtual void die() = 0;  //死亡
};

#endif// !__UNIT_H_