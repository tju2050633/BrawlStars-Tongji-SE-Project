#ifndef __AI_H_
#define __AI_H_

#include "cocos2d.h"

USING_NS_CC;
class Brawler;
class Entity;
class AI :public Node {
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //操纵的英雄
	CC_SYNTHESIZE(INT32, _attackRange, AttackRange); //攻击距离

	CC_SYNTHESIZE(Entity*, _nearestBox, NearestBox);			//最近的宝箱
	CC_SYNTHESIZE(Sprite*, _nearestBuff, NearestBuff);			//最近的buff
	CC_SYNTHESIZE(Brawler*, _nearestBrawler, _nearestBrawler);	//最近的英雄
	CC_SYNTHESIZE(Vec2, _destination, Destination);				//目的地
	CC_SYNTHESIZE(Entity*, _target, Target);					//目标，宝箱、追杀的英雄，为空时逃跑
	CC_SYNTHESIZE(Vec2, _targetPos, TargetPos);					//目标坐标
	CC_SYNTHESIZE(float, _angle, Angle);					//目标的角度

	bool _X_Direction_Modity;	//X方向速度修正，true为正x方向
	bool _Y_Direction_Modity;	//Y方向速度修正，true为正y方向

	bool _animationAvailable;	//防止动画播放太频繁
	bool _isAvoidingWall;		//防止速度修正太频繁

public:
	CREATE_FUNC(AI);
	virtual bool init();
	virtual void update(float dt);//每帧刷新，改变移速
	void updateMoveSpeed();	//刷新移速
	void updateBushVisibility();	//刷新草丛视野情况
	void update05s(float dt);	//每0.5秒刷新，做出行为
	void update1s(float dt);	//每秒刷新，更新目标、最近的宝箱

	void updateNearestBrawler();
	void updateNearestBox();
	void updateNearestBuff();

};

#endif // !__AI_H_
