#ifndef __WALKING_STATE_H_
#define __WALKING_STATE_H_

#include "Utils/FSMState.h"

USING_NS_CC;

class AI;
class WalkingState : public FSMState
{
public:
	virtual void execute(AI* ai, MsgType _msgType);
};

#endif	//__WALKING_STATE_H_