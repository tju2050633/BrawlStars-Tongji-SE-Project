#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity;
class Brawler : public Entity {
    /*����*/
    CC_SYNTHESIZE(INT32, _bulletNum, BulletNum);//�ӵ�����
    CC_SYNTHESIZE(float, _reloadTime, ReloadTime);//�ӵ�װ��ʱ��
    CC_SYNTHESIZE(INT32, _energyBar, EnergyBar);//���������ͷŴ����ã�

public:
    /*��������ͳ�ʼ������*/
    CREATE_FUNC(Bullet);
    virtual bool init();

    void takeBuff();               //���buff����������
    virtual void castAbility() {}  //�ͷŴ���
};

#endif// !__BRAWLER_H_