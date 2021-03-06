#ifndef __NITA_H_
#define __NITA_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Entity/Bear.h"

USING_NS_CC;

class Nita : public Brawler {
public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Nita);
	virtual bool init();

	virtual void attack(float angle);
	virtual void castAbility(float angle);
	virtual bool takeDamage(INT32 damage)override;
	virtual void die()override;
};

#endif // !__NITA_H_