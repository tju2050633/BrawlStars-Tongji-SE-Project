#ifndef __BULLET_H_
#define __BULLET_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity;
class Brawler;
class Bullet : public Node {
	/*属性*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);          //精灵
	CC_SYNTHESIZE(Brawler*, _launcher, Launcher);//发射者
	CC_SYNTHESIZE(INT32, _damage, Damage);		//伤害
	CC_SYNTHESIZE(INT32, _speed, Speed);		//速度
	CC_SYNTHESIZE(float, _range, Range);		//射程

public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Bullet);
	virtual bool init();

	/*绑定精灵*/
	void bindSprite(Sprite* sprite);

	/*设置属性*/
	void setAttributes(INT32 damage, INT32 speed, INT32 range, Brawler* launcher);

	void launch(Vec2 direction);      //接受一个角度参数，向该方向发射出去
	void collide(Entity* target);     //接受一个Entity参数，碰撞时调用
};

#endif// __BULLET_H_