#ifndef __STU_H_
#define __STU_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

class Stu : public Brawler {

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Stu);
	virtual bool init();

	void attack(float angle);
	void castAbility(float angle);
};

#endif // !__STU_H_