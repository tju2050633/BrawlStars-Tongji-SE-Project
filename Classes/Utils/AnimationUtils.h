#ifndef __ANIMATION_UTILS_H
#define __ANIMATION_UTILS_H

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class Brawler;
class AnimationUtils {
public:
    /*ö������Ӣ��*/
    enum BrawlerEnum {
        Shelly,
        Nita,
        Primo,
        Stu
    };
    static string Brawlers[4];

    /*ö�����ж�������*/
    enum TypeEnum {
        Top,
        Left,
        Bottom,
        Right
    };
    static string Types[4];

    /*��ȡ��������*/
    static Animate* getAnimate(BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);
    
    /*Ӣ�����ж���*/
    static void runAnimate(Brawler* targetBrawler,BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop);

    /*Ӣ��ֹͣ����*/
    static void stopAnimate(Brawler* targetBrawler, BrawlerEnum brawler, TypeEnum type);
};


#endif //__ANIMATION_UTILS_H