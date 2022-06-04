#ifndef __PRIMO_H_
#define __PRIMO_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

class Primo : public Brawler {

public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Primo);
	virtual bool init();

	virtual void attack(float angle)override;
	virtual void castAbility(float angle)override;
	virtual void takeDamage(INT32 damage)override;
	virtual void die()override;
};

#endif // !__PRIMO_H_