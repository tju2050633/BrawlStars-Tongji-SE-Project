#ifndef __CONTROLLER_LISTENER_H_
#define __CONTROLLER_LISTENER_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

/*Player类需要继承的接口*/
//控制器可以设置、获取目标位置、速度
class ControllerListener {
public:
	/*设置和获取位置*/
	virtual void setTargetPostion(Vec2 position) = 0;
	virtual Vec2 getTargetPostion() = 0;
	/*设置和获取目标当前速度（不是英雄固有移速属性）*/
	virtual void setTargetMoveSpeedX(int speedX) = 0;
	virtual void setTargetMoveSpeedY(int speedY) = 0;
	virtual INT32 getTargetMoveSpeedX() = 0;
	virtual INT32 getTargetMoveSpeedY() = 0;
	/*获取英雄*/
	virtual Brawler* getTargetBrawler() = 0;
};

#endif // !__CONTROLLER_LISTENER_H_
