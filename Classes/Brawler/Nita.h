#ifndef __NITA_H_
#define __NITA_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

class Nita : public Brawler {

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Nita);
	virtual bool init();

	virtual void attack(float angle);
	virtual void castAbility(float angle);
	virtual void takeDamage(INT32 damage)override;
	virtual void die()override;
};

#endif // !__NITA_H_