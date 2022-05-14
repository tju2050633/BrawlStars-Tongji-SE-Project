#ifndef __MENU_H_
#define __MENU_H_

#include "cocos2d.h"

/*【行动指示】菜单界面
这部分主要实现init函数，那几个回调函数只是切换场景而已，基本不用太管
init部分也写的差不多了，还剩素材路径、坐标y值两个细节，都用中文标出来了
还有音频，需要单独一位同学负责一下，SimpleAudioEngine似乎是cocos引擎音频的一部分

另外，关于problemLoading()这个函数每个cpp都写一遍感觉不好，应该可以写一份然后external拓展作用文件啥的？
这块知识忘了，还记得的就给他优化一下
*/

class Menu : public cocos2d::Scene
{
public:
    /*创建场景和初始化*/
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    /*按键回调函数*/
    void menuSinglePlayerCallback(cocos2d::Ref* pSender);   //单人模式
    void menuMultiPlayerCallback(cocos2d::Ref* pSender);    //多人模式
    void menuSettingsCallback(cocos2d::Ref* pSender);       //游戏设置
    void menuInstructionCallback(cocos2d::Ref* pSender);    //游戏说明
    void menuQuitCallback(cocos2d::Ref* pSender);           //退出游戏
    
    /*自动生成create()的宏*/
    CREATE_FUNC(Menu);
};

#endif //__MENU_H_