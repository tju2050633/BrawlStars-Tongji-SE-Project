#ifndef __BOX_H_
#define __BOX_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Box : public Entity {
public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Box);
	virtual bool init();

	void die()override;  //被打碎，掉落buff
};

#endif// !__BOX_H_