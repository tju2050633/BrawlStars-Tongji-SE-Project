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
		GameScene,
		Settings,
		Instruction,
		Room
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
	static AllBrawler _brawler;		//���ʹ�õ�brawl
	static INT32 _brawlerNumber;	//brawler����
	static INT32 _shellyNumber;		//AI��Shelly����
	static INT32 _nitaNumber;		//AI��Nita����
	static INT32 _primoNumber;		//AI��Primo����
	static INT32 _stuNumber;		//AI��Stu����

	/*��������*/
	static bool _musicOn;			//��¼�Ƿ񲥷�����
	static bool _effectOn;			//��¼�Ƿ񲥷���Ч

	/*���õ�problemLoading����������ظ�*/
	static void problemLoading(const char* filename);

	/*���ã��л�����ʱʹ�ã�����Ϊ�ö�����ö����*/
	static void changeScene(AllScenes targetScene);

	/*���ּ��ر���ͼ�ķ�ʽ*/
	enum setBGimageWith {
		TextureCache,
		SpriteFrameCache
	};
	/*���ñ���ͼ�����г����๲�ã�loadWay���ּ��ر���ͼ��ʽ*/
	static void setBGimage(const char* filename, Layer* layer, setBGimageWith loadWay);
};

#endif // !_SCENE_UTILS_H_