#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/SceneManager.h"
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

	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*开场动画的一些临时代码*/
	float x = visibleSize.width / 2 + origin.x;
	float y = visibleSize.height / 2 + origin.y;
	auto StartSprite = Sprite::create("Bnt_settings.png");
	StartSprite->setPosition(Vec2(x, y));
	this->addChild(StartSprite);

	TransitionScene* reScene = NULL;
	Scene* s = Scene::create();

	float t = 2.2f;
	reScene = TransitionJumpZoom::create(t, s);

	this->addChild(reScene);
	auto TransSprite = Sprite::create("HelloWorld.png");
	TransSprite->setPosition(Vec2(x, y));
	s->addChild(TransSprite);

	SceneManager::getInstance()->changeScene(SceneManager::GameMenu);
	return true;
}