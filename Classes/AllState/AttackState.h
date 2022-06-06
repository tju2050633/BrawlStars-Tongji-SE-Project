#ifndef __ATTACK_STATE_H_
#define __ATTACK_STATE_H_

#include "Utils/FSMState.h"

USING_NS_CC;
class AI;
class AttackState : public FSMState
{
public:
	virtual void execute(AI* ai, MsgType _msgType);
};

#endif  //__ATTACK_STATE_H_