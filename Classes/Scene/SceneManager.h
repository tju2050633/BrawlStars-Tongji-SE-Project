#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "cocos2d.h"

USING_NS_CC;

class SceneManager:public Ref{
private:
	/*单例类对象指针*/
	static SceneManager* _sceneManager;

public:
	/*枚举所有场景*/
	enum AllScenes {
        OpeningAnimation,
		GameMenu,
		Settings,
		Instruction,
		SelectMap,
		SelectBrawler,
        GameScene
	};

	/*获取单例类对象指针*/
	static SceneManager* getInstance();

    /*本类不需要初始化，总是返回true*/
	virtual bool init();

    /*切换场景时使用，参数为该对象内枚举数*/
	void changeScene(AllScenes targetScene);
};

#endif // !_SCENEMANAGER_H_