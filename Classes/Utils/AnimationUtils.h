#ifndef __ANIMATION_UTILS_H
#define __ANIMATION_UTILS_H

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class Entity;
class AnimationUtils {
public:
    /*ö������Ӣ��*/
    enum EntityEnum {
        Shelly,
        Nita,
        Primo,
        Stu,
        bear
    };
    static string Entities[5];

    /*ö�����ж�������*/
    enum TypeEnum {
        Top,
        Left,
        Bottom,
        Right,
        boom,
        Attack
    };
    static string Types[6];
    static TypeEnum _state;//ʵʱ��¼��ɫ״̬

    /*��ȡ��������*/
    static Animate* getAnimate(EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);
    
    /*Ӣ�����ж���*/
    static void runAnimate(Entity* target, EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);

    /*Ӣ��ֹͣ����*/
    static void stopAnimate(Entity* target, EntityEnum entity, TypeEnum type);
};


#endif //__ANIMATION_UTILS_H