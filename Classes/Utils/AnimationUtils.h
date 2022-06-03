#ifndef __ANIMATION_UTILS_H
#define __ANIMATION_UTILS_H

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class Brawler;
class AnimationUtils {
public:
    /*枚举所有英雄*/
    enum BrawlerEnum {
        Shelly,
        Nita,
        Primo,
        Stu
    };
    static string Brawlers[4];

    /*枚举所有动画种类*/
    enum TypeEnum {
        Top,
        Left,
        Bottom,
        Right
    };
    static string Types[4];

    /*获取动画序列*/
    static Animate* getAnimate(BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);
    
    /*英雄运行动画*/
    static void runAnimate(Brawler* targetBrawler,BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);

    /*英雄停止动画*/
    static void stopAnimate(Brawler* targetBrawler, BrawlerEnum brawler, TypeEnum type);
};


#endif //__ANIMATION_UTILS_H