#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;

class Player: public Node, public ControllerListener {
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //操纵的英雄
	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //当前x方向速度
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //当前y方向速度

public:
	/*创建函数*/
	CREATE_FUNC(Player);
	virtual bool init();

	/*实现继承自ControllerListener的纯虚函数*/

	/*设置、获取位置*/
	virtual void setTargetPosition(Vec2 position);
	virtual Vec2 getTargetPosition();
	/*设置和获取目标当前速度（不是英雄固有移速属性）*/
	virtual void setTargetMoveSpeedX(int speedX);
	virtual void setTargetMoveSpeedY(int speedY);
	virtual INT32 getTargetMoveSpeedX();
	virtual INT32 getTargetMoveSpeedY();
	/*获取英雄*/
	virtual Brawler* getTargetBrawler();
};

#endif // !__PLAYER_H_
