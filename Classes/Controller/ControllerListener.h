#ifndef __CONTROLLER_LISTENER_H_
#define __CONTROLLER_LISTENER_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

/*Player����Ҫ�̳еĽӿ�*/
//�������������á���ȡĿ��λ�á��ٶ�
class ControllerListener {
public:
	/*���úͻ�ȡλ��*/
	virtual void setTargetPostion(Vec2 position) = 0;
	virtual Vec2 getTargetPostion() = 0;
	/*���úͻ�ȡĿ�굱ǰ�ٶȣ�����Ӣ�۹����������ԣ�*/
	virtual void setTargetMoveSpeedX(int speedX) = 0;
	virtual void setTargetMoveSpeedY(int speedY) = 0;
	virtual INT32 getTargetMoveSpeedX() = 0;
	virtual INT32 getTargetMoveSpeedY() = 0;
	/*��ȡӢ��*/
	virtual Brawler* getTargetBrawler() = 0;
};

#endif // !__CONTROLLER_LISTENER_H_
