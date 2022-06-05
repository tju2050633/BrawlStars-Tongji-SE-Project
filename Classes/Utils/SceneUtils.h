#ifndef _SCENE_UTILS_H_
#define _SCENE_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;

class SceneUtils
{
public:
	/*枚举所有场景*/
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
	/*枚举所有地图*/
	enum AllMap
	{
		MapA,
		MapB,
		MapC
	};
	/*枚举所有英雄*/
	enum AllBrawler
	{
		Shelly,
		Primo,
		Nita,
		Stu
	};
	/*静态成员变量，存储切换场景时用到的信息*/
	static AllMap _map;				
	static AllBrawler _brawler;		//玩家使用的brawl
	static INT32 _brawlerNumber;	//brawler总数
	static INT32 _shellyNumber;		//AI中Shelly个数
	static INT32 _nitaNumber;		//AI中Nita个数
	static INT32 _primoNumber;		//AI中Primo个数
	static INT32 _stuNumber;		//AI中Stu个数

	/*音乐设置*/
	static bool _musicOn;			//记录是否播放音乐
	static bool _effectOn;			//记录是否播放音效

	/*共用的problemLoading，避免代码重复*/
	static void problemLoading(const char* filename);

	/*共用，切换场景时使用，参数为该对象内枚举数*/
	static void changeScene(AllScenes targetScene);

	/*两种加载背景图的方式*/
	enum setBGimageWith {
		TextureCache,
		SpriteFrameCache
	};
	/*放置背景图，所有场景类共用，loadWay区分加载背景图方式*/
	static void setBGimage(const char* filename, Layer* layer, setBGimageWith loadWay);
};

#endif // !_SCENE_UTILS_H_