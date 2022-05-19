#include <vector>
#include <string>
#include "cocos2d.h"
#include "Scene/SelectMap.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
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
	if (!Scene::init())
	{
		return false;
	}

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("选择地图背景音乐", true);
	}

	/*菜单*/
	initMenu();

	/*背景*/
	SceneManager::setBGimage("BGimage2.png", this);

	return true;
}

/*选择地图 初始化菜单 ×*/
void SelectMap::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "MapA", "MapB", "MapC", "Back" };
	//按钮回调函数
	vector<void (SelectMap::*)(Ref* pSender)> CallbackVector = {
		&SelectMap::menuMapACallback,&SelectMap::menuMapBCallback,
		&SelectMap::menuMapCCallback,&SelectMap::menuBackCallback
	};
	//按钮尺寸
	vector<float> ScaleVector = { 0.2 ,0.15,0.1,1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),Vec2(0, 1)
	};
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 2 * visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 4 + origin.y),
		Vec2(origin.x, visibleSize.height + origin.y)
	};
	/*逐个创建按钮，分配信息，存入Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		string filename = "button/" + stringVector[i];
		MenuItemImage* button = MenuItemImage::create(
			filename + "-Normal.png",
			filename + "-Active.png",
			bind(CallbackVector[i], this, std::placeholders::_1)
		);
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneManager::problemLoading(filename.c_str());//
		else
		{
			button->setScale(ScaleVector[i]);
			button->setAnchorPoint(AnchorVector[i]);
			button->setPosition(PositionVector[i]);
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
	SceneManager::map = SceneManager::AllMap::MapA;
	SceneManager::getInstance()->changeScene(SceneManager::SelectBrawler);
}

/*选择地图 地图B回调函数 √*/
void SelectMap::menuMapBCallback(cocos2d::Ref* pSender)
{
	SceneManager::map = SceneManager::AllMap::MapB;
	SceneManager::getInstance()->changeScene(SceneManager::SelectBrawler);
}

/*选择地图 地图C回调函数 √*/
void SelectMap::menuMapCCallback(cocos2d::Ref* pSender)
{
	SceneManager::map = SceneManager::AllMap::MapC;
	SceneManager::getInstance()->changeScene(SceneManager::SelectBrawler);
}

/*选择地图 返回回调函数 √*/
//场景从SelectMap切换至GameMenu
void SelectMap::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::GameMenu);
}