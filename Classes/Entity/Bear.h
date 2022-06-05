#ifndef __BEAR_H_
#define __BEAR_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Brawler;
class Bear : public Entity {
	CC_SYNTHESIZE(Brawler*, _owner, Owner);//����
	CC_SYNTHESIZE(Entity*, _target, Target);//����Ŀ��

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Bear);
	virtual bool init();

	void update(float dt);
};

#endif// !__BEAR_H_