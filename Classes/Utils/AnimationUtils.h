#ifndef __ANIMATION_UTILS_H
#define __ANIMATION_UTILS_H

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class Entity;
class AnimationUtils {
public:
    /*枚举所有英雄*/
    enum EntityEnum {
        Shelly,
        Nita,
        Primo,
        Stu,
        bear
    };
    static string Entities[5];

    /*枚举所有动画种类*/
    enum TypeEnum {
        Top,
        Left,
        Bottom,
        Right,
        boom,
        Attack
    };
    static string Types[6];
    static TypeEnum _state;//实时记录角色状态

    /*获取动画序列*/
    static Animate* getAnimate(EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);
    
    /*英雄运行动画*/
    static void runAnimate(Entity* target, EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);

    /*英雄停止动画*/
    static void stopAnimate(Entity* target, EntityEnum entity, TypeEnum type);
};


#endif //__ANIMATION_UTILS_H