#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
private:
	/*初始化 地图*/
	void initMap();

	/*初始化 人物*/
	void initBrawler();

	/*初始化 标签*/
	void initLabel();

	/*初始化 按钮*/
	void initButton();

	/*初始化 操作器*/
	void initControler();

	/*表情 回调函数*/
	void menuEmotionCallback(Ref *pSender);

	/*返回 回调函数*/
	void menuBackCallback(Ref *pSender);

public:
	/*创建场景和初始化*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
};

#endif // !__GAME_SCENE_H_