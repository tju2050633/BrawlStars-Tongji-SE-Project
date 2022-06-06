#ifndef __FSMSYSTEM_H__
#define  __FSMSYSTEM_H__

#include "cocos2d.h"

USING_NS_CC;

class FSMState;
class AI;
class FSMSystem : public Node {
private:
	//自定义事件监听器
	CC_SYNTHESIZE(EventListenerCustom*, _attackListenerCustom, AttackListenerCustom);

	//AI对象
	AI* _ai;

	//存放当前状态类
	FSMState* _curState;

	/*自定义事件回调函数
	此处以攻击事件为例
	*/
	void onRecvWantToAttack(EventCustom* Event);

public:
	//添加各类自定义事件的监听器
	bool init(AI* ai);
	static FSMSystem* createWithAI(AI* ai);
	virtual void update(float dt);

	void changeState(FSMState* state);   /* 切换状态 */
};

#endif