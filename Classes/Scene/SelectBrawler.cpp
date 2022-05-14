#include "cocos2d.h"
#include "SelectBrawler.h"
#include "GameScene.h"
#include "SelectMap.h"

USING_NS_CC;

/*获得场景对象 √*/
//init需接受参数，不能用CREATE_FUNC自动生成的create()
//用以下模板（仅需改init内参数，效果和create()一样）
Scene* SelectBrawler::createScene(char map)
{
	auto scene = new(std::nothrow)SelectBrawler;
	if (scene && scene->init(char map))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

/*错误处理函数 √*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

/*选英雄菜单场景初始化 ×*/
bool SelectBrawler::init(char map)
{
	/*初始化父类*/
	if (!Scene::init())
	{
		return false;
	}

    /*初始化本类成员变量*/
    m_map = map;

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("选择地图背景音乐", true);
	}

	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*雪莉*/
	MenuItemImage *ShellyButton = MenuItemImage::create(
		"雪莉-Normal.png",
		"雪莉-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuShellyCallback, this)
	);
	if (ShellyButton == nullptr ||
		ShellyButton->getContentSize().width <= 0 ||
		ShellyButton->getContentSize().height <= 0)
	{
		problemLoading("'雪莉'");
	}
	else
	{
		float x = /*雪莉 x值*/;
		float y = /*雪莉 y值*/;
		ShellyButton->setPosition(Vec2(x, y));
	}

    /*普里莫*/
	MenuItemImage *PrimoButton = MenuItemImage::create(
		"普里莫-Normal.png",
		"普里莫-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuPrimoCallback, this)
	);
	if (PrimoButton == nullptr ||
		PrimoButton->getContentSize().width <= 0 ||
		PrimoButton->getContentSize().height <= 0)
	{
		problemLoading("'普里莫'");
	}
	else
	{
		float x = /*普里莫 x值*/;
		float y = /*普里莫 y值*/;
		PrimoButton->setPosition(Vec2(x, y));
	}

    /*妮塔*/
	MenuItemImage *NitaButton = MenuItemImage::create(
		"妮塔-Normal.png",
		"妮塔-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuNitaCallback, this)
	);
	if (NitaButton == nullptr ||
		NitaButton->getContentSize().width <= 0 ||
		NitaButton->getContentSize().height <= 0)
	{
		problemLoading("'妮塔'");
	}
	else
	{
		float x = /*妮塔 x值*/;
		float y = /*妮塔 y值*/;
		NitaButton->setPosition(Vec2(x, y));
	}

    /*斯图*/
	MenuItemImage *StuButton = MenuItemImage::create(
		"斯图-Normal.png",
		"斯图-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuSituCallback, this)
	);
	if (StuButton == nullptr ||
		StuButton->getContentSize().width <= 0 ||
		StuButton->getContentSize().height <= 0)
	{
		problemLoading("'斯图'");
	}
	else
	{
		float x = /*斯图 x值*/;
		float y = /*斯图 y值*/;
		StuButton->setPosition(Vec2(x, y));
	}

    /*返回按钮*/
	MenuItemImage *backButton = MenuItemImage::create(
		"返回按钮-Normal.png",
		"返回按钮-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuBackCallback, this)
	);
	if (backButton == nullptr ||
		backButton->getContentSize().width <= 0 ||
		backButton->getContentSize().height <= 0)
	{
		problemLoading("'返回按钮'");
	}
	else
	{
		float x = /*返回按钮 x值*/;
		float y = /*返回按钮 y值*/;
		backButton->setPosition(Vec2(x, y));
	}

	
	/*总的菜单，包含以上菜单选项*/
	Menu* selectMap = Menu::create(ShellyButton, PrimoButton, NitaButton, StuButton, backButton, NULL);
	selectMap->setPosition(Vec2::ZERO);
	this->addChild(selectMap, 1);

	/*背景*/
	auto background = Sprite::create("选择英雄背景图片");
	if (background == nullptr)
	{
		problemLoading("'选择英雄背景图片'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}

	return true;
}

/*选择英雄 雪莉回调函数 √*/
//场景从SelectBrawler切换至GameScene（参数为m_map, "Shelly"）
void SelectBrawler::menuShellyCallback(cocos2d::Ref* pSender)
{
    /*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = GameScene::create(m_map,"Shelly");    //需要向下一场景传递参数（表示选择的地图和英雄）
	Director::getInstance()->replaceScene(          //具体参数类型和值需完善
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*选择英雄 普里莫回调函数 √*/
//场景从SelectBrawler切换至GameScene（参数为m_map, "Primo"）
void SelectBrawler::menuPrimoCallback(cocos2d::Ref* pSender)
{
    /*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = GameScene::create(m_map, "Primo");    //需要向下一场景传递参数（表示选择的地图和英雄）
	Director::getInstance()->replaceScene(          //具体参数类型和值需完善
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*选择英雄 妮塔回调函数 √*/
//场景从SelectBrawler切换至GameScene（参数为m_map, "Nita"）
void SelectBrawler::menuNitaCallback(cocos2d::Ref* pSender)
{
    /*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = GameScene::create(m_map, "Nita");    //需要向下一场景传递参数（表示选择的地图和英雄）
	Director::getInstance()->replaceScene(          //具体参数类型和值需完善
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*选择英雄 斯图回调函数 √*/
//场景从SelectBrawler切换至GameScene（参数为m_map, "Situ"）
void SelectBrawler::menuSituCallback(cocos2d::Ref* pSender)
{
    /*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = GameScene::create(m_map, "Situ");    //需要向下一场景传递参数（表示选择的地图和英雄）
	Director::getInstance()->replaceScene(          //具体参数类型和值需完善
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*菜单 返回回调函数 √*/
//场景从SelectBrawler切换至SelectMap
void SelectBrawler::menuBackCallback(cocos2d::Ref* pSender)
{
    /*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = SelectMap::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}