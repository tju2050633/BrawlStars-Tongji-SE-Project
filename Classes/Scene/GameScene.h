#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"

/*【行动指示】游戏主界面
*/

class GameScene : public cocos2d::Scene
{
private:
    char m_map;       //地图A、B、C，暂定
    String m_brawler; //英雄Shelly、Primo、Nita、Stu，暂定

public:
    /*创建场景和初始化*/
    static cocos2d::Scene* createScene(char map, String brawler);
    virtual bool init(char map, String brawler);
    
};

#endif //__GAMESCENE_H_