#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"

USING_NS_CC;

class Unit : public Sprite {
    /*����*/
    CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);  //Ѫ��
    CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);//������
    CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);      //����
    CC_SYNTHESIZE(float, _attackInterval, AttackInterval);  //�������
    CC_SYNTHESIZE(bool, _inBush, InBush);           //�ж��Ƿ��ڲݴ���
    //Ѫ�����
    //����ķ���
public:
    virtual void attack();  //������û��ʵ��
    void takeDamage(INT32 damage);  //�����˺�
    virtual void moveTo();  //�ƶ�������ΪĿ���
    virtual void die() = 0;  //����
};

#endif// !__UNIT_H_