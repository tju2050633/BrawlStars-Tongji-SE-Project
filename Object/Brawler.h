#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Unit.h"

USING_NS_CC;

class Brawler : public Unit {
    /*����*/
    CC_SYNTHESIZE(INT32, _bulletNum, BulletNum);//�ӵ�����
    CC_SYNTHESIZE(float, _reloadTime, ReloadTime);//�ӵ�װ��ʱ��
    CC_SYNTHESIZE(INT32, _energyBar, EnergyBar);//���������ͷŴ����ã�

public:
    void takeBuff();//���buff����������
    virtual void castAbility() = 0;//�ͷŴ���
};

#endif// !__BRAWLER_H_