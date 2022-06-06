#ifndef __AI_H_
#define __AI_H_

#include "cocos2d.h"
#include "Utils/FSMSystem.h"

USING_NS_CC;
class FSMSystem;
class Brawler;
class AI :public Node {
private:
	//��ŵ�ǰ״̬��
	FSMSystem* myFSMSystem;
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //���ݵ�Ӣ��

public:
	virtual bool init();
	virtual void update(float dt);

	//��ȡ����״̬��
	FSMSystem* getFSM();

	/*��ȡӢ��*/
	virtual Brawler* getTargetBrawler();

	/*�ж��Ƿ��л�״̬������bool*/
	bool FoundEnemy();
	bool FoundEnergy();
	bool KilledEnemy();

	/*������Ϊ*/
	void Attack();
	void GetEnergy();
	void Wander();
};

#endif // !__AI_H_
