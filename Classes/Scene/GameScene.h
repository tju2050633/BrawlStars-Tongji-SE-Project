#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;

class GameScene : public Scene
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

	/*自动生成create()的宏*/
	CREATE_FUNC(GameScene);
};

#endif // !__GAMESCENE_H_