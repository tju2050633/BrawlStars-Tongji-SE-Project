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

	/*声音*/
	// auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// if (!audio->isBackgroundMusicPlaying()) {
	// 	audio->playBackgroundMusic("开场动画音乐", true);
	// }

	/*预加载所有图片、音频等资源*/
	PreloadResource();

	/*背景*/
	SceneUtils::setBGimage("OpeningAnimation.png", this, 2);

	return true;
}

/*预加载所有图片、音频等资源*/
void OpeningAnimation::PreloadResource()
{
	/*后续背景图*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	///*菜单按钮*/
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("button.plist");
	//Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Settings-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Settings-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Instruction-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Instruction-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Quit-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Quit-Active.png");
	/*地图按钮*/
	/*Director::getInstance()->getTextureCache()->addImage("button/MapA-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapA-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Active.png");*/

	Director::getInstance()->getTextureCache()->addImageAsync("BGimage/BGimage.plist", CC_CALLBACK_1(OpeningAnimation::plistImageAsyncCallback, this));
}

/*切换到游戏菜单*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

void OpeningAnimation::plistImageAsyncCallback(Texture2D* texture) {
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("BGimage/BGimage.plist", texture);
}