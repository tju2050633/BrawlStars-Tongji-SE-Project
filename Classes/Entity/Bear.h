#ifndef __BEAR_H_
#define __BEAR_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Brawler;
class Bear : public Entity {
	CC_SYNTHESIZE(Brawler*, _owner, Owner);//主人
	CC_SYNTHESIZE(Entity*, _target, Target);//攻击目标

public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Bear);
	virtual bool init();

	void update(float dt);
};

#endif// !__BEAR_H_