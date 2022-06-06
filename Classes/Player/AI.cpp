#include "Player/AI.h"
#include "Entity/Brawler.h"

/*AI��ʼ�����Զ�����״̬����ÿ֡����״̬����update*/
bool AI::init()
{
	/*��ʼ��״̬��*/
	myFSMSystem = FSMSystem::createWithAI(this);
	myFSMSystem->retain();

	this->scheduleUpdate();
	return true;
}

FSMSystem* AI::getFSM()
{
	return this->myFSMSystem;
}

/*��ȡӢ��*/
Brawler* AI::getTargetBrawler()
{
	return _brawler;
}

void AI::update(float dt)
{
	this->myFSMSystem->update(dt);
}
/*�ж��Ƿ��л�״̬������bool*/
bool AI::FoundEnemy()
{
	return true;
}

bool AI::FoundEnergy()
{
	return true;
}

bool AI::KilledEnemy()
{
	return true;
}

/*������Ϊ*/
void AI::Attack()
{
	/*

	*/
	return;
}

void AI::GetEnergy()
{

}
void AI::Wander()
{

}