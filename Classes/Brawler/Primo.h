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

	void attack(float angle);
	void castAbility(float angle);
};

#endif // !__PRIMO_H_