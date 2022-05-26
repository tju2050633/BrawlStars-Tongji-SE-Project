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

	/*三秒后进入菜单界面*/
	scheduleOnce(SEL_SCHEDULE(&OpeningAnimation::EnterMenu), 3.0f);

	/*声音*/
	// auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// if (!audio->isBackgroundMusicPlaying()) {
	// 	audio->playBackgroundMusic("开场动画音乐", true);
	// }

	/*背景*/
	SceneUtils::setBGimage("BGimage/OpeningAnimation.png", this);

	/*欢迎图标*/
	LoadWelcomeLabel();

	/*预加载所有图片、音频等资源*/
	PreloadResource();

	return true;
}

/*加载欢迎图标*/
void OpeningAnimation::LoadWelcomeLabel()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	auto welcome = Sprite::create("BGimage/Welcome.png");

	if (welcome == nullptr)
	{
		SceneUtils::problemLoading("'BGimage/Welcome.png'");
	}
	else
	{
		welcome->setScale(0.3);
		welcome->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 75));
		this->addChild(welcome, 1);
	}
}

/*预加载所有图片、音频等资源*/
void OpeningAnimation::PreloadResource()
{
	/*后续背景图*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	/*菜单按钮*/
	Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/Settings-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/Settings-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/Instruction-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/Instruction-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/Quit-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/Quit-Active.png");
	/*地图按钮*/
	Director::getInstance()->getTextureCache()->addImage("button/MapA-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapA-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Active.png");
}

/*切换到游戏菜单*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}