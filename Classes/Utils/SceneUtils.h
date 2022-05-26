#ifndef _SCENE_UTILS_H_
#define _SCENE_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;

class SceneUtils
{
public:
	/*ö�����г���*/
	enum AllScenes
	{
		OpeningAnimation,
		GameMenu,
		SelectMap,
		SelectBrawler,
		GameScene
	};
	/*ö�����в�*/
	enum AllLayers
	{
		Settings,
		Instruction
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
	static AllMap _map;
	static AllBrawler _brawler;
	static int _brawlerNumber;

	/*���õ�problemLoading����������ظ�*/
	static void problemLoading(const char* filename);

	/*���ã��л�����ʱʹ�ã�����Ϊ�ö�����ö����*/
	static void changeScene(AllScenes targetScene);

	/*���ã������*/
	static void addLayer(AllLayers targetLayer, Scene* currentScene);

	/*���ñ���ͼ�����г����๲��*/
	static void setBGimage(const char* filename, Layer* layer);
};

#endif // !_SCENE_UTILS_H_