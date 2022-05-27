#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Brawler : public Entity {
	/*属性*/
	CC_SYNTHESIZE(INT32, _ammo, Ammo);//弹药
	CC_SYNTHESIZE(INT32, _energyBar, EnergyBar);//充能条（释放大招用）

public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Brawler);
	virtual bool init();

	/*继承自Entity的函数*/
	void move();  //移动
	void die();  //死亡

	/*Brawler特有函数*/
	void takeBuff();               //获得buff，增加属性
	
};

#endif// !__BRAWLER_H_