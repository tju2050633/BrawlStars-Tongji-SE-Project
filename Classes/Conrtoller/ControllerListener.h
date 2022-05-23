#ifndef __CONTROLLER_LISTENER_H_
#define __CONTROLLER_LISTENER_H_

#include "cocos2d.h"

USING_NS_CC;

/*Player类需要继承的接口，规定了设置、获取监听对象坐标两个接口函数*/
class ControllerListener {
public:
	virtual void setTargetPostion(int x, int y) = 0;
	virtual Point getTargetPostion() = 0;
};

#endif // !__CONTROLLER_LISTENER_H_
