#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"

/*【行动指示】游戏主界面
*/

class GameScene : public cocos2d::Scene
{
private:
	std::string m_map;       //地图A、B、C，暂定
	std::string m_brawler; //英雄Shelly、Primo、Nita、Stu，暂定

public:
	/*创建场景和初始化*/
	static cocos2d::Scene* createScene(std::string map, std::string brawler);
	virtual bool init(std::string map, std::string brawler);

	/*自定义create()*/
	GameScene* create(std::string map, std::string brawler);
};

#endif //__GAMESCENE_H_