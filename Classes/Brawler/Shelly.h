#ifndef __SHELLY_H_
#define __SHELLY_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

class Shelly : public Brawler {
	
public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Shelly);
	virtual bool init();

	void attack(float angle);
	void castAbility(float angle);
};

#endif // !__SHELLY_H_
