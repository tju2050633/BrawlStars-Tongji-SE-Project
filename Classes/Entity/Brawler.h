#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Entity/Bullet.h"
#include "Utils/AnimationUtils.h"

USING_NS_CC;

class Brawler : public Entity {
	/*属性*/
	CC_SYNTHESIZE(INT32, _ammo, Ammo);//弹药
	CC_SYNTHESIZE(INT32, _energyBar, EnergyBar);//充能条（释放大招用）

	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //当前x方向速度
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //当前y方向速度

	/*已发射的子弹*/
	Vector<Bullet*> _bulletVector;

	/*范围指示器*/
	CC_SYNTHESIZE(Sprite*, _rangeIndicator, RangeIndicator); 

	/*动画需要的英雄枚举类*/
	CC_SYNTHESIZE(AnimationUtils::BrawlerEnum, _animateBrawler, AnimateBrawler);

public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Brawler);
	virtual bool init();

	void update(float dt)override;

	/*继承自Entity的函数*/
	void die();  //死亡

	/*Brawler特有函数*/
	virtual void castAbility(float angle) {}
	void takeBuff();               //获得buff，增加属性
	
};

#endif// !__BRAWLER_H_