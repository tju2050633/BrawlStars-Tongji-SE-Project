#ifndef __BEAR_H_
#define __BEAR_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Brawler;
class Bear : public Entity{
	CC_SYNTHESIZE(Brawler*, _owner, Owner);//主人
	CC_SYNTHESIZE(INT32, _attackRange, AttackRange); //攻击距离

	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //当前x方向速度
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //当前y方向速度

	CC_SYNTHESIZE(Brawler*, _target, Target);				//目标英雄
	CC_SYNTHESIZE(Vec2, _targetPos, TargetPos);				//目标坐标

	bool _X_Direction_Modity;	//X方向速度修正，true为正x方向
	bool _Y_Direction_Modity;	//Y方向速度修正，true为正y方向

	bool _animationAvailable;	//防止动画播放太频繁
	bool _isAvoidingWall;		//防止速度修正太频繁

public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Bear);
	virtual bool init();

	void update(float dt);
	void update05s(float dt);
	void update1s(float dt);

	void updateMoveSpeed();

	void attack(Brawler* brawler);
	void die()override;
};

#endif// !__BEAR_H_