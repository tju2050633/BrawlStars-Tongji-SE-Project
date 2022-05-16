#include "cocos2d.h"
#include "Instruction.h"
#include "GameMenu.h"

USING_NS_CC;

/*获得场景对象 √*/
Scene* Instruction::createScene()
{
	return Instruction::create();
}

/*游戏说明场景初始化 ×*/
bool Instruction::init()
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