#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;

class Player: public Node, public ControllerListener {
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //���ݵ�Ӣ��
	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //��ǰx�����ٶ�
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //��ǰy�����ٶ�

public:
	/*��������*/
	CREATE_FUNC(Player);
	virtual bool init();

	/*ʵ��ControllerListener�ӿ�*/
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
