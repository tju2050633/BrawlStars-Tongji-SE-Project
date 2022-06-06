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
	/*EventListenerCustom�� �Զ����¼�����������PlayerController�������õ��ļ���������������
	�����¼����ͷ�ϵͳ����������Ϊ���棩
	* MsgTypes�ɼ������
	*/
	_attackListenerCustom = EventListenerCustom::create(MsgTypes[0], CC_CALLBACK_1(FSMSystem::onRecvWantToAttack, this));
	//�˴��ɼ����Ӹ���״̬��Listener

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

/*ִ�й��� �ص�����*/
void FSMSystem::onRecvWantToAttack(EventCustom* Event)
{
	this->_curState->execute(_ai, MsgAttack);
}