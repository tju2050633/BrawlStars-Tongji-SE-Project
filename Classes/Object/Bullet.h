#ifndef __BULLET_H_
#define __BULLET_H_

#include "cocos2d.h"
#include "Object/Unit.h"
#include "Object/Brawler.h"

USING_NS_CC;

class Bullet : public Sprite {
    /*����*/
    CC_SYNTHESIZE(Brawler*, _launcher, Launcher);//������
    CC_SYNTHESIZE(INT32, _damage, Damage);		//�˺�
    CC_SYNTHESIZE(float, _range, Range);		//���
    CC_SYNTHESIZE(float, _speed, Speed);		//�����ٶ�

public:
    /*��������ͳ�ʼ������*/
    static Bullet* create(const std::string& filename, Brawler* launcher, INT32 damage, float range, float speed);
    virtual bool init(const std::string& filename, Brawler* launcher, INT32 damage, float range, float speed);

    void launch(float angle);      //����һ���ǶȲ�������÷������ȥ
    void collide(Unit* target);     //����һ��Unit��������ײʱ����
};

#endif// __BULLET_H_