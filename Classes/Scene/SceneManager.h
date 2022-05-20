#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "cocos2d.h"

USING_NS_CC;

class SceneManager : public Ref
{
private:
	/*单例类对象指针*/
	static SceneManager *_sceneManager;

public:
	/*枚举所有场景*/
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
	static AllMap map;
	static AllBrawler brawler;
	static int brawler_number;

	/*获取单例类对象指针*/
	static SceneManager *getInstance();

	/*本类不需要初始化，总是返回true*/
	virtual bool init();

	/*共用的problemLoading，避免代码重复*/
	static void problemLoading(const char *filename);

	/*共用，切换场景时使用，参数为该对象内枚举数*/
	static void changeScene(AllScenes targetScene);

	/*放置背景图，所有场景类共用*/
	static void setBGimage(const char *filename, Scene *scene);
};

#endif // !_SCENEMANAGER_H_