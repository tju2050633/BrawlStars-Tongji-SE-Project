#include "Object/Unit.h"

/*�����˺�*/
void Unit::takeDamage(INT32 damage)
{
    _healthPoint -= damage;
    if(_healthPoint <= 0)
    {
        die();
    }
}

/*�ƶ�������ΪĿ���*/
void Unit::moveTo()
{
}
