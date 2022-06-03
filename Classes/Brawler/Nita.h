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

	void attack(float angle);
	void castAbility(float angle);
};

#endif // !__NITA_H_