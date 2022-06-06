#include "Player/AI.h"
#include "Entity/Brawler.h"

/*AI初始化：自动创建状态机，每帧调用状态机的update*/
bool AI::init()
{
	/*初始化状态机*/
	myFSMSystem = FSMSystem::createWithAI(this);
	myFSMSystem->retain();

	this->scheduleUpdate();
	return true;
}

FSMSystem* AI::getFSM()
{
	return this->myFSMSystem;
}

/*获取英雄*/
Brawler* AI::getTargetBrawler()
{
	return _brawler;
}

void AI::update(float dt)
{
	this->myFSMSystem->update(dt);
}
/*判断是否切换状态，返回bool*/
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

/*具体行为*/
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