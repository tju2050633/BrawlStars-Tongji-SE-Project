#ifndef __BOX_H_
#define __BOX_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Box : public Entity {
public:
	virtual void die();  //ËÀÍö£¬µôÂäbuff
};

#endif// !__BOX_H_