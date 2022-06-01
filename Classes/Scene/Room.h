#ifndef __ROOM_H_
#define __ROOM_H_

#include "cocos2d.h"

USING_NS_CC;

class Room : public Layer
{
public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Room);

	/*返回 回调函数*/
	void menuBackCallback(Ref* pSender);
};

#endif // !__ROOM_H_