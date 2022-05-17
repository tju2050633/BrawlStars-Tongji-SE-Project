#include "Object/Unit.h"

/*承受伤害*/
void Unit::takeDamage(INT32 damage)
{
    _healthPoint -= damage;
    if(_healthPoint <= 0)
    {
        die();
    }
}

/*移动，参数为目标地*/
void Unit::moveTo()
{
}
