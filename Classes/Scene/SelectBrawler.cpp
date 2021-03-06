#include "cocos2d.h"
#include <vector>
#include <string>
#include "Scene/SelectBrawler.h"
#include "Utils/SceneUtils.h"
#include "Utils/MusicUtils.h"

USING_NS_CC;
using namespace std;


/*获得场景对象 √*/
Scene* SelectBrawler::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectBrawler::create();
	scene->addChild(layer);
	return scene;
}

/*选英雄菜单场景初始化 ×*/
bool SelectBrawler::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	/*菜单*/
	initMenu();

	/*背景*/
	SceneUtils::setBGimage("BGimage/Background.png", this, SceneUtils::setBGimageWith::TextureCache);

	return true;
}

/*选择英雄 初始化菜单 ×*/
void SelectBrawler::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "Shelly", "Primo", "Nita", "Stu", "Back" };
	//按钮回调函数
	vector<void (SelectBrawler::*)(Ref* pSender)> CallbackVector = {
		&SelectBrawler::menuShellyCallback,
		&SelectBrawler::menuPrimoCallback,
		&SelectBrawler::menuNitaCallback,
		&SelectBrawler::menuStuCallback,
		&SelectBrawler::menuBackCallback };
	//按钮尺寸
	vector<float> ScaleVector = { 0.4, 0.4, 0.4, 0.4, 1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0, 1) };
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(1 * visibleSize.width / 5 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(2 * visibleSize.width / 5 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(3 * visibleSize.width / 5 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(4 * visibleSize.width / 5 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(origin.x, visibleSize.height + origin.y) };

	/*逐个创建按钮，分配信息，存入Vector*/
	for (ssize_t i = 0; i < stringVector.size(); i++)
	{
		MenuItemImage* button = MenuItemImage::create(
			"Portrait/" + stringVector.at(i) + "-Normal.png",
			"Portrait/" + stringVector.at(i) + "-Active.png",
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

/*选择英雄 雪莉回调函数 √*/
void SelectBrawler::menuShellyCallback(cocos2d::Ref* pSender)
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	
	SceneUtils::_brawler = SceneUtils::AllBrawler::Shelly;
	SceneUtils::changeScene(SceneUtils::AllScenes::Room);
}

/*选择英雄 普里莫回调函数 √*/
void SelectBrawler::menuPrimoCallback(cocos2d::Ref* pSender)
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	
	SceneUtils::_brawler = SceneUtils::AllBrawler::Primo;
	SceneUtils::changeScene(SceneUtils::AllScenes::Room);
}

/*选择英雄 妮塔回调函数 √*/
void SelectBrawler::menuNitaCallback(cocos2d::Ref* pSender)
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	
	SceneUtils::_brawler = SceneUtils::AllBrawler::Nita;
	SceneUtils::changeScene(SceneUtils::AllScenes::Room);
}

/*选择英雄 斯图回调函数 √*/
void SelectBrawler::menuStuCallback(cocos2d::Ref* pSender)
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	
	SceneUtils::_brawler = SceneUtils::AllBrawler::Stu;
	SceneUtils::changeScene(SceneUtils::AllScenes::Room);
}

/*菜单 返回回调函数 √*/
void SelectBrawler::menuBackCallback(cocos2d::Ref* pSender)
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	
	SceneUtils::changeScene(SceneUtils::AllScenes::SelectMap);
}