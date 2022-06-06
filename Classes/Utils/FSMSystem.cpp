#include "Utils/FSMSystem.h"
#include "Utils/FSMState.h"
#include "Utils/MsgType.h"

FSMSystem* FSMSystem::createWithAI(AI* ai)
{
	FSMSystem* fsm = new FSMSystem();
	if (fsm && fsm->init(ai))
	{
		fsm->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(fsm);
		fsm = NULL;
	}
	return fsm;
}

bool FSMSystem::init(AI* ai)
{
	this->_curState = NULL;
	this->_ai = ai;
	/*EventListenerCustom类 自定义事件监听器（与PlayerController类中运用到的键盘鼠标监听器类似
	但此事件类型非系统触发，需人为干涉）
	* MsgTypes可继续添加
	*/
	_attackListenerCustom = EventListenerCustom::create(MsgTypes[0], CC_CALLBACK_1(FSMSystem::onRecvWantToAttack, this));
	//此处可继续加各种状态的Listener

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_attackListenerCustom, 1);
	return true;
}

void FSMSystem::update(float dt)
{

}

void FSMSystem::changeState(FSMState* state)
{
	CC_SAFE_DELETE(_curState);
	this->_curState = state;
}

/*执行攻击 回调函数*/
void FSMSystem::onRecvWantToAttack(EventCustom* Event)
{
	this->_curState->execute(_ai, MsgAttack);
}