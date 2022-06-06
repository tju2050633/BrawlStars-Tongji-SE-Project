#ifndef __FSMSYSTEM_H__
#define  __FSMSYSTEM_H__

#include "cocos2d.h"

USING_NS_CC;

class FSMState;
class AI;
class FSMSystem : public Node {
private:
	//�Զ����¼�������
	CC_SYNTHESIZE(EventListenerCustom*, _attackListenerCustom, AttackListenerCustom);

	//AI����
	AI* _ai;

	//��ŵ�ǰ״̬��
	FSMState* _curState;

	/*�Զ����¼��ص�����
	�˴��Թ����¼�Ϊ��
	*/
	void onRecvWantToAttack(EventCustom* Event);

public:
	//��Ӹ����Զ����¼��ļ�����
	bool init(AI* ai);
	static FSMSystem* createWithAI(AI* ai);
	virtual void update(float dt);

	void changeState(FSMState* state);   /* �л�״̬ */
};

#endif