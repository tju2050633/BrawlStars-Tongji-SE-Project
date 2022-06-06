#include "AllState/AttackState.h"
#include "AllState/WalkingState.h"

void AttackState::execute(AI* ai, MsgType _msgType)
{
	switch (_msgType)
	{
		case MsgAttack:

			break;
	}
	if(ai->KilledEnemy())
	{
		ai->Attack();
		ai->getFSM()->changeState(new WalkingState());
	}
	return;
}