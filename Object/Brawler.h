#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Unit.h"

USING_NS_CC;

class Brawler : public Unit {
    /*属性*/
    CC_SYNTHESIZE(INT32, _bulletNum, BulletNum);//子弹数量
    CC_SYNTHESIZE(float, _reloadTime, ReloadTime);//子弹装填时间
    CC_SYNTHESIZE(INT32, _energyBar, EnergyBar);//充能条（释放大招用）

public:
    void takeBuff();//获得buff，增加属性
    virtual void castAbility() = 0;//释放大招
};

#endif// !__BRAWLER_H_