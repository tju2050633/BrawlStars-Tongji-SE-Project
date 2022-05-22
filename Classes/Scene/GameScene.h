#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
private:
	/*��ʼ�� ��ͼ*/
	void initMap();

	/*��ʼ�� ����*/
	void initBrawler();

	/*��ʼ�� ��ǩ*/
	void initLabel();

	/*��ʼ�� ��ť*/
	void initButton();

	/*��ʼ�� ������*/
	void initControler();

	/*���� �ص�����*/
	void menuEmotionCallback(Ref *pSender);

	/*���� �ص�����*/
	void menuBackCallback(Ref *pSender);

public:
	/*���������ͳ�ʼ��*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
};

#endif // !__GAME_SCENE_H_