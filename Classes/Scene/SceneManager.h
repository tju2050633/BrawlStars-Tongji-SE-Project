#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "cocos2d.h"

USING_NS_CC;

class SceneManager:public Ref{
private:
	/*���������ָ��*/
	static SceneManager* _sceneManager;

public:
	/*ö�����г���*/
	enum AllScenes {
        OpeningAnimation,
		GameMenu,
		Settings,
		Instruction,
		SelectMap,
		SelectBrawler,
        GameScene
	};

	/*��ȡ���������ָ��*/
	static SceneManager* getInstance();

    /*���಻��Ҫ��ʼ�������Ƿ���true*/
	virtual bool init();

    /*�л�����ʱʹ�ã�����Ϊ�ö�����ö����*/
	void changeScene(AllScenes targetScene);
};

#endif // !_SCENEMANAGER_H_