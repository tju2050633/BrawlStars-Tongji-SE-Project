#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;

class GameScene : public Scene
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

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(GameScene);
};

#endif // !__GAMESCENE_H_