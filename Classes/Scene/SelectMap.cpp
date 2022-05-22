#include <string>
#include "cocos2d.h"
#include "Scene/SelectMap.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;
using namespace std;

/*获得场景对象 √*/
Scene* SelectMap::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectMap::create();
	scene->addChild(layer);
	return scene;
}

/*选择地图 场景初始化 ×*/
bool SelectMap::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	// auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// if (!audio->isBackgroundMusicPlaying())
	// {
	// 	audio->playBackgroundMusic("选择地图背景音乐", true);
	// }

	/*菜单*/
	initMenu();

	/*背景*/
	SceneUtils::setBGimage("BGimage/SelectMap", this);

	return true;
}

/*选择地图 初始化菜单 ×*/
void SelectMap::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "MapA", "MapB", "MapC", "Back" };
	//按钮回调函数
	vector<void (SelectMap::*)(Ref* pSender)> CallbackVector = {
		&SelectMap::menuMapACallback, &SelectMap::menuMapBCallback,
		&SelectMap::menuMapCCallback, &SelectMap::menuBackCallback };
	//按钮尺寸
	vector<float> ScaleVector = { 0.2, 0.15, 0.1, 1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0, 1) };
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 2 * visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 4 + origin.y),
		Vec2(origin.x, visibleSize.height + origin.y) };
	/*逐个创建按钮，分配信息，存入Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItemImage* button = MenuItemImage::create(
			StringUtils::format("button/%s-Normal.png", stringVector.at(i)),
			StringUtils::format("button/%s-Active.png", stringVector.at(i)),
			bind(CallbackVector.at(i), this, std::placeholders::_1));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneUtils::problemLoading(stringVector.at(i).c_str());
		else
		{
			button->setScale(ScaleVector.at(i));
			button->setAnchorPoint(AnchorVector.at(i));
			button->setPosition(PositionVector.at(i));
		}
		MenuItemVector.pushBack(button);
	}

	/*总的菜单，包含以上菜单选项*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*选择地图 地图A回调函数 √*/
void SelectMap::menuMapACallback(cocos2d::Ref* pSender)
{
	SceneUtils::_map = SceneUtils::AllMap::MapA;
	SceneUtils::changeScene(SceneUtils::SelectBrawler);
}

/*选择地图 地图B回调函数 √*/
void SelectMap::menuMapBCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_map = SceneUtils::AllMap::MapB;
	SceneUtils::changeScene(SceneUtils::SelectBrawler);
}

/*选择地图 地图C回调函数 √*/
void SelectMap::menuMapCCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_map = SceneUtils::AllMap::MapC;
	SceneUtils::changeScene(SceneUtils::SelectBrawler);
}

/*选择地图 返回回调函数 √*/
//场景从SelectMap切换至GameMenu
void SelectMap::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::GameMenu);
}