#ifndef __BOX_H_
#define __BOX_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Box : public Entity {
public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Box);
	virtual bool init();

	void die()override;  //�����飬����buff
};

#endif// !__BOX_H_