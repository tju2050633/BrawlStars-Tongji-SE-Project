#include <cmath>
#include "Brawler/Primo.h"
#include "Constant/Const.h"

bool Primo::init()
{
	if (!Brawler::init())
	{
		return false;
	}
	setMoveSpeed(PRIMO_MS);
	setAnimateBrawler(AnimationUtils::Primo);
	return true;
}

void Primo::attack(float angle)
{

}

void Primo::castAbility(float angle)
{

}