#ifndef __CONTROLLER_LISTENER_H_
#define __CONTROLLER_LISTENER_H_

#include "cocos2d.h"

USING_NS_CC;

/*Player����Ҫ�̳еĽӿڣ��涨�����á���ȡ�����������������ӿں���*/
class ControllerListener {
public:
	virtual void setTargetPostion(int x, int y) = 0;
	virtual Point getTargetPostion() = 0;
};

#endif // !__CONTROLLER_LISTENER_H_
