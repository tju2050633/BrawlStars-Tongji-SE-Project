#include "cocos2d.h"
#include "Settings.h"
#include "GameMenu.h"

USING_NS_CC;

/*获得场景对象 √*/
Scene* Settings::createScene()
{
	auto scene = Scene::create();
	auto layer = Settings::create();
	scene->addChild(layer);
	return scene;
}

/*游戏设置场景初始化 ×*/
bool Settings::init()
{
	/*初始化父类*/
	if (!Scene::init())
	{
		return false;
	}

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
		//audio->playBackgroundMusic("选择地图背景音乐", true);
	//}

	return true;
}