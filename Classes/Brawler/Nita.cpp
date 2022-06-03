#include <cmath>
#include "Brawler/Nita.h"
#include "Constant/Const.h"

bool Nita::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	setMoveSpeed(NITA_MS);
	setAnimateBrawler(AnimationUtils::Nita);
	return true;
}

void Nita::attack(float angle)
{

}

void Nita::castAbility(float angle)
{

}