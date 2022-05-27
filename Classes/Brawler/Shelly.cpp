#include "Brawler/Shelly.h"
#include "Constant/Const.h"

bool Shelly::init()
{
	setMoveSpeed(SHELLY_MS);
	return true;
}