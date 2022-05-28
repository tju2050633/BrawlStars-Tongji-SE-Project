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

	/*ʵ�ּ̳���ControllerListener�Ĵ��麯��*/

	/*���á���ȡλ��*/
	virtual void setTargetPosition(Vec2 position);
	virtual Vec2 getTargetPosition();
	/*���úͻ�ȡĿ�굱ǰ�ٶȣ�����Ӣ�۹����������ԣ�*/
	virtual void setTargetMoveSpeedX(int speedX);
	virtual void setTargetMoveSpeedY(int speedY);
	virtual INT32 getTargetMoveSpeedX();
	virtual INT32 getTargetMoveSpeedY();
	/*��ȡӢ��*/
	virtual Brawler* getTargetBrawler();
};

#endif // !__PLAYER_H_
