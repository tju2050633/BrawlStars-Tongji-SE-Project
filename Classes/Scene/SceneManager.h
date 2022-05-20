#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "cocos2d.h"

USING_NS_CC;

class SceneManager : public Ref
{
private:
	/*���������ָ��*/
	static SceneManager *_sceneManager;

public:
	/*ö�����г���*/
	enum AllScenes
	{
		OpeningAnimation,
		GameMenu,
		Settings,
		Instruction,
		SelectMap,
		SelectBrawler,
		GameScene
	};
	/*ö�����е�ͼ*/
	enum AllMap
	{
		MapA,
		MapB,
		MapC
	};
	/*ö������Ӣ��*/
	enum AllBrawler
	{
		Shelly,
		Primo,
		Nita,
		Stu
	};
	/*��̬��Ա�������洢�л�����ʱ�õ�����Ϣ*/
	static AllMap map;
	static AllBrawler brawler;
	static int brawler_number;

	/*��ȡ���������ָ��*/
	static SceneManager *getInstance();

	/*���಻��Ҫ��ʼ�������Ƿ���true*/
	virtual bool init();

	/*���õ�problemLoading����������ظ�*/
	static void problemLoading(const char *filename);

	/*���ã��л�����ʱʹ�ã�����Ϊ�ö�����ö����*/
	static void changeScene(AllScenes targetScene);

	/*���ñ���ͼ�����г����๲��*/
	static void setBGimage(const char *filename, Scene *scene);
};

#endif // !_SCENEMANAGER_H_