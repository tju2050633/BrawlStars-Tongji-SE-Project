#include "cocos2d.h"
#include "Settings.h"
#include "GameMenu.h"
#include "Utils/SceneUtils.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	 /*背景*/
	SceneUtils::setBGimage("BGimage/Background.png", this, SceneUtils::setBGimageWith::TextureCache);
	
	//菜单
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//返回按钮

	MenuItemImage* button = MenuItemImage::create("button/Back-Normal.png", "button/Back-Active.png",
		[](Ref* pSender)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
			SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
		});

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
