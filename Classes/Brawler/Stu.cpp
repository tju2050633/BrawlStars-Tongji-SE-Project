#include <cmath>
#include "Brawler/Stu.h"
#include "Constant/Const.h"

bool Stu::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	setMoveSpeed(STU_MS);
	setAnimateBrawler(AnimationUtils::Stu);
	return true;
}

void Stu::attack(float angle)
{
	
}

void Stu::castAbility(float angle)
{

}