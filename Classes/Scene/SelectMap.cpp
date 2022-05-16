#include "cocos2d.h"
#include "SelectMap.h"
#include "SelectBrawler.h"
#include "GameMenu.h"

USING_NS_CC;

/*获得场景对象 √*/
Scene* SelectMap::createScene()
{
	return SelectMap::create();
}

/*错误处理函数 √*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

/*选模式菜单场景初始化 ×*/
bool SelectMap::init()
{
	/*初始化父类*/
	if (!Scene::init())
	{
		return false;
	}

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("选择地图背景音乐", true);
	}

	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*地图A选项*/
	MenuItemImage* MapAButton = MenuItemImage::create(
		"地图A-Normal.png",
		"地图A-Active.png",
		CC_CALLBACK_1(SelectMap::menuMapACallback, this)
	);
	if (MapAButton == nullptr ||
		MapAButton->getContentSize().width <= 0 ||
		MapAButton->getContentSize().height <= 0)
	{
		problemLoading("'地图A按钮'");
	}
	else
	{
		float x = /*地图A x值*/;
		float y = /*地图A y值*/;
		MapAButton->setPosition(Vec2(x, y));
	}

	/*地图B选项*/
	MenuItemImage* MapBButton = MenuItemImage::create(
		"地图B-Normal.png",
		"地图B-Active.png",
		CC_CALLBACK_1(SelectMap::menuMapBCallback, this)
	);
	if (MapBButton == nullptr ||
		MapBButton->getContentSize().width <= 0 ||
		MapBButton->getContentSize().height <= 0)
	{
		problemLoading("'地图B按钮'");
	}
	else
	{
		float x = /*地图B x值*/;
		float y = /*地图B y值*/;
		MapBButton->setPosition(Vec2(x, y));
	}

	/*地图C选项*/
	MenuItemImage* MapCButton = MenuItemImage::create(
		"地图C-Normal.png",
		"地图C-Active.png",
		CC_CALLBACK_1(SelectMap::menuMapCCallback, this)
	);
	if (MapCButton == nullptr ||
		MapCButton->getContentSize().width <= 0 ||
		MapCButton->getContentSize().height <= 0)
	{
		problemLoading("'地图C按钮'");
	}
	else
	{
		float x = /*地图C x值*/;
		float y = /*地图C y值*/;
		MapCButton->setPosition(Vec2(x, y));
	}

	/*返回按钮*/
	MenuItemImage* backButton = MenuItemImage::create(
		"返回按钮-Normal.png",
		"返回按钮-Active.png",
		CC_CALLBACK_1(SelectMap::menuBackCallback, this)
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
	Menu* selectMap = Menu::create(MapAButton, MapBButton, MapCButton, backButton, NULL);
	selectMap->setPosition(Vec2::ZERO);
	this->addChild(selectMap, 1);

	/*背景*/
	auto background = Sprite::create("选择地图背景图片");
	if (background == nullptr)
	{
		problemLoading("'选择地图背景图片'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}

	return true;
}

/*选择地图 地图A回调函数 √*/
//场景从SelectMap切换至SelectBrawler（参数为'A'）
void SelectMap::menuMapACallback(cocos2d::Ref* pSender)
{
	/*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = SelectBrawler::create('A');    //需要向下一场景传递参数（表示选择的地图）
	Director::getInstance()->replaceScene(          //具体参数类型和值需完善
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*选择地图 地图B回调函数 √*/
//场景从SelectMap切换至SelectBrawler（参数为'B'）
void SelectMap::menuMapBCallback(cocos2d::Ref* pSender)
{
	/*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = SelectBrawler::create('B');
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*选择地图 地图C回调函数 √*/
//场景从SelectMap切换至SelectBrawler（参数为'C'）
void SelectMap::menuMapCCallback(cocos2d::Ref* pSender)
{
	/*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = SelectBrawler::create('C');
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*选择地图 返回回调函数 √*/
//场景从SelectMap切换至Menu
void SelectMap::menuBackCallback(cocos2d::Ref* pSender)
{
	/*切换场景两步：1.定义nextScene2.导演调用replaceScene*/
	auto nextScene = Menu::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}