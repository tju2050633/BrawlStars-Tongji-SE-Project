#include "cocos2d.h"
#include "Scene/SelectBrawler.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*获得场景对象 √*/
//init需接受参数，不能用CREATE_FUNC自动生成的create()
//用以下模板（仅需改init内参数，效果和create()一样）
Scene* SelectBrawler::createScene(SceneManager::AllMap map)
{
	auto scene = Scene::create();
	auto layer = SelectBrawler::create(map);
	scene->addChild(layer);
	return scene;
}

/*自定义create()*/
SelectBrawler* SelectBrawler::create(SceneManager::AllMap map)
{
	auto scene = new(std::nothrow)SelectBrawler;
	if (scene && scene->init(map))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

/*选英雄菜单场景初始化 ×*/
bool SelectBrawler::init(SceneManager::AllMap map)
{
	/*初始化父类*/
	if (!Scene::init())
	{
		return false;
	}

	/*初始化本类成员变量*/
	_map = map;

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	/*lx
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("选择地图背景音乐", true);
	}*/

	/*菜单*/
	initMenu();

	/*背景*/
	SceneManager::setBGimage("BGimage3.png", this);

	return true;
}

/*选择英雄 初始化菜单 ×*/
void SelectBrawler::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "Shelly", "Primo", "Nita", "Stu", "Back"};
	//按钮回调函数
	vector<void (SelectBrawler::*)(Ref* pSender)> CallbackVector = {
		&SelectBrawler::menuShellyCallback,& SelectBrawler::menuPrimoCallback,
		& SelectBrawler::menuNitaCallback,& SelectBrawler::menuStuCallback,
		& SelectBrawler::menuBackCallback,
	};
	//按钮尺寸
	vector<float> ScaleVector = { 1,1,1,1,1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),Vec2(0.5, 0.5),
		Vec2(0, 1)
	};
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(2 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(3 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(4 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
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

/*选择英雄 雪莉回调函数 √*/
//场景从SelectBrawler切换至GameScene（参数为m_map, "Shelly"）
void SelectBrawler::menuShellyCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Shelly;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*选择英雄 普里莫回调函数 √*/
void SelectBrawler::menuPrimoCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Primo;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*选择英雄 妮塔回调函数 √*/
void SelectBrawler::menuNitaCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Nita;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*选择英雄 斯图回调函数 √*/
void SelectBrawler::menuStuCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Stu;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*菜单 返回回调函数 √*/
//场景从SelectBrawler切换至SelectMap
void SelectBrawler::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::SelectMap);
}