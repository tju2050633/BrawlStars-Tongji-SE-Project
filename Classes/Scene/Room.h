#ifndef __ROOM_H_
#define __ROOM_H_

#include "cocos2d.h"

USING_NS_CC;

class Room : public Layer
{
public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Room);

	/*���� �ص�����*/
	void menuBackCallback(Ref* pSender);
};

#endif // !__ROOM_H_