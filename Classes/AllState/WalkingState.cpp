#include "Utils/FSMState.h"
#include "AllState/WalkingState.h"
#include "AllState/AttackState.h"

void WalkingState::execute(AI* ai, MsgType _msgType)
{
	switch (_msgType)
	{
		case MsgAttack:

			break;
	}
	if(ai->FoundEnemy())
	{
		ai->Attack();
		ai->getFSM()->changeState(new AttackState());
	}
	return;
}