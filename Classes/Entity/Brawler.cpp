#include "cocos2d.h"
#include "Entity/Brawler.h"

virtual bool init()
{
    return true;
}

/*���buff����������*/
void Brawler::takeBuff()
{
    _healthPoint += 400;
    //�ӹ�����...
}