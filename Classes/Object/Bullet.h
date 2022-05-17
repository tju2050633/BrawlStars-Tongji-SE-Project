#ifndef __BULLET_H_
#define __BULLET_H_

#include "cocos2d.h"
#include "Object/Unit.h"
#include "Object/Brawler.h"

USING_NS_CC;

class Bullet : public Sprite {
    /*属性*/
    CC_SYNTHESIZE(Brawler*, _launcher, Launcher);//发射者
    CC_SYNTHESIZE(INT32, _damage, Damage);		//伤害
    CC_SYNTHESIZE(float, _range, Range);		//射程
    CC_SYNTHESIZE(float, _speed, Speed);		//弹道速度

public:
    /*创建对象和初始化函数*/
    static Bullet* create(const std::string& filename, Brawler* launcher, INT32 damage, float range, float speed);
    virtual bool init(const std::string& filename, Brawler* launcher, INT32 damage, float range, float speed);

    void launch(float angle);      //接受一个角度参数，向该方向发射出去
    void collide(Unit* target);     //接受一个Unit参数，碰撞时调用
};

#endif// __BULLET_H_