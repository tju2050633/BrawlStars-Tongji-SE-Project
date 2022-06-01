#include "cocos2d.h"
#include "Settings.h"
#include "GameMenu.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;

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
	if (!Layer::init())
	{
		return false;
	}

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
		//audio->playBackgroundMusic("选择地图背景音乐", true);
	//}

	 /*背景*/
	SceneUtils::setBGimage("BGimage/Background.png", this, SceneUtils::setBGimageWith::TextureCache);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//菜单
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//返回按钮

	MenuItemImage* button = MenuItemImage::create("button/Back-Normal.png", "button/Back-Active.png",
		CC_CALLBACK_1(Settings::menuBackCallback, this));

	if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
		SceneUtils::problemLoading("button/Back-Normal.png");
	else
	{
		button->setScale(1);
		button->setAnchorPoint(Vec2(0, 1));
		button->setPosition(Vec2(origin.x, visibleSize.height + origin.y));
	}
	menu->addChild(button);
	return true;
}

//场景从Settings切换至GameMenu
void Settings::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}