#ifndef __SHELLY_H_
#define __SHELLY_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

class Shelly : public Brawler {
	
public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Shelly);
	virtual bool init();

	virtual void attack(float angle);
	virtual void castAbility(float angle);
	virtual bool takeDamage(INT32 damage)override;
	virtual void die()override;
};

#endif // !__SHELLY_H_
