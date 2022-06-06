#ifndef __AI_H_
#define __AI_H_

#include "cocos2d.h"
#include "Utils/FSMSystem.h"

USING_NS_CC;
class FSMSystem;
class Brawler;
class AI :public Node {
private:
	//存放当前状态类
	FSMSystem* myFSMSystem;
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //操纵的英雄

public:
	virtual bool init();
	virtual void update(float dt);

	//获取有限状态机
	FSMSystem* getFSM();

	/*获取英雄*/
	virtual Brawler* getTargetBrawler();

	/*判断是否切换状态，返回bool*/
	bool FoundEnemy();
	bool FoundEnergy();
	bool KilledEnemy();

	/*具体行为*/
	void Attack();
	void GetEnergy();
	void Wander();
};

#endif // !__AI_H_
