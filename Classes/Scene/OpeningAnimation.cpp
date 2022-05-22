#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/SceneUtils.h"
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
	scheduleOnce(schedule_selector(OpeningAnimation::EnterMenu), 3.0f);

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
void LoadWelcomeLabel()
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
void PreloadResource()
{
	/*后续背景图*/
	TextureCache::getInstance()->addImageAsync("BGimage/GameMenu.png");
	TextureCache::getInstance()->addImageAsync("BGimage/SelectMap.png");
	TextureCache::getInstance()->addImageAsync("BGimage/SelectBrawler.png");
	/*按钮图片*/
	TextureCache::getInstance()->addImageAsync("button/SinglePlayer-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/SinglePlayer-Active.png");
	TextureCache::getInstance()->addImageAsync("button/MultiPlayer-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MultiPlayer-Active.png");
	TextureCache::getInstance()->addImageAsync("button/Settings-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/Settings-Active.png");
	TextureCache::getInstance()->addImageAsync("button/Instruction-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/Instruction-Active.png");
	TextureCache::getInstance()->addImageAsync("button/Quit-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/Quit-Active.png");
	/*选择地图图片*/
	TextureCache::getInstance()->addImageAsync("button/MapA-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MapA-Active.png");
	TextureCache::getInstance()->addImageAsync("button/MapB-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MapB-Active.png");
	TextureCache::getInstance()->addImageAsync("button/MapC-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MapC-Active.png");
}

/*切换到游戏菜单*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::GameMenu);
}
