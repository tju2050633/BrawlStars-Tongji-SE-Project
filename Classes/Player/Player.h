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

	/*实现ControllerListener接口*/
	void setTargetPostion(Vec2 position)
	{
		setPosition(position);
	}
	Vec2 getTargetPostion()
	{
		return getPosition();
	}
	void setTargetMoveSpeedX(int speedX)
	{
		setMoveSpeedX(speedX);
	}
	void setTargetMoveSpeedY(int speedY)
	{
		setMoveSpeedY(speedY);
	}
	INT32 getTargetMoveSpeedY()
	{
		return _moveSpeedX;
	}
	INT32 getTargetMoveSpeedX()
	{
		return _moveSpeedY;
	}
	Brawler* getTargetBrawler()
	{
		return _brawler;
	}
};

#endif // !__PLAYER_H_
