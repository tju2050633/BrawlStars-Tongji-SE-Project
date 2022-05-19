#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/SceneManager.h"
#include "Scene/GameMenu.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*获得场景对象 √*/
Scene* OpeningAnimation::createScene()
{
	auto scene = Scene::create();
	auto layer = OpeningAnimation::create();
	scene->addChild(layer);
	return scene;
}

/*开场动画场景初始化 ×*/
bool OpeningAnimation::init()
{
	/*初始化父类*/
	if (!Scene::init())
	{
		return false;
	}

	/*声音*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("选择地图背景音乐", true);
	}

	/*背景*/
	SceneManager::setBGimage("BGimage1.png", this);

	/*加载欢迎图标*/
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	auto welcome = Sprite::create("Welcome.png");
	welcome->setScale(0.3);

	if (welcome == nullptr)
	{
		SceneManager::problemLoading("'Welcome.png'");
	}
	else
	{
		welcome->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 75));
		this->addChild(welcome, 1);
	}

	/*三秒后进入菜单界面*/
	scheduleOnce(schedule_selector(OpeningAnimation::EnterMenu), 3.0f);
	
	return true;
}

void OpeningAnimation::EnterMenu(float dt)
{
	SceneManager::changeScene(SceneManager::GameMenu);
}
