#ifndef __BULLET_H_
#define __BULLET_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity;
class Brawler;
class Bullet : public Entity {
	/*属性*/
	CC_SYNTHESIZE(Brawler*, _launcher, Launcher);//发射者
	CC_SYNTHESIZE(float, _range, Range);		//射程

public:
	/*构造函数*/
	Bullet();

	/*创建对象和初始化函数*/
	CREATE_FUNC(Bullet);
	virtual bool init();

	/*自定义属性*/
	void setAttributes(INT32 attackDamage, INT32 moveSpeed, float range, Brawler* launcher);

	void launch(Vec2 direction);      //接受一个角度参数，向该方向发射出去
	void collide(Entity* target);     //接受一个Entity参数，碰撞时调用
};

#endif// __BULLET_H_