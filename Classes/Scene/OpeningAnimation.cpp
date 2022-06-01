#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Utils/SceneUtils.h"
#include "Scene/GameMenu.h"

USING_NS_CC;

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
	if (!Layer::init())
	{
		return false;
	}

	/*三秒后进入菜单界面*/    //改为2秒
	scheduleOnce(SEL_SCHEDULE(&OpeningAnimation::EnterMenu), 1.5f);   // why 1s ？

	/*预加载所有图片、音频等资源*/
	PreloadResource();

	/*背景*/
	SceneUtils::setBGimage("OpeningAnimation.png", this, SceneUtils::setBGimageWith::SpriteFrameCache);

	return true;
}

/*预加载所有图片、音频等资源*/
void OpeningAnimation::PreloadResource()
{
	/*精灵图*/
	Director::getInstance()->getTextureCache()->addImage("trophy.png");
	/*后续背景图*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	/*加载背景图plist*/
	Director::getInstance()->getTextureCache()->addImageAsync("BGimage/BGimage.plist", CC_CALLBACK_1(OpeningAnimation::plistImageAsyncCallback, this));
	/*加载控制器plist*/
	Director::getInstance()->getTextureCache()->addImageAsync("Controller/Controller.plist", CC_CALLBACK_1(OpeningAnimation::plistControllerAsyncCallback, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Controller/AttackButton.plist", CC_CALLBACK_1(OpeningAnimation::plistAttackAsyncCallback, this));
	/*加载动画帧plist*/
}

/*切换到游戏菜单*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

void OpeningAnimation::plistImageAsyncCallback(Texture2D* texture) 
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("BGimage/BGimage.plist", texture);
}

void OpeningAnimation::plistControllerAsyncCallback(Texture2D* texture)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Controller/Controller.plist");
}

void OpeningAnimation::plistAttackAsyncCallback(Texture2D* texture)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Controller/AttackButton.plist");
}