#include "cocos2d.h"
#include <string>
#include <fstream>
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Utils/SceneUtils.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;


/*获得场景对象 √*/
Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

/*菜单 场景初始化 ×*/
bool GameMenu::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	/*声音*/
	

	/*菜单*/
	initMenu();

	/*奖杯*/
	initTrophy();

	/*背景*/
	SceneUtils::setBGimage("BGimage/GameMenu.png", this, SceneUtils::setBGimageWith::TextureCache);

	return true;
}

/*菜单 初始化菜单*/
void GameMenu::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "SinglePlayer", "MultiPlayer", "Settings", "Instruction", "Quit" };
	//按钮回调函数
	vector<void (GameMenu::*)(Ref* pSender)> CallbackVector = { &GameMenu::menuSinglePlayerCallback,
																&GameMenu::menuMultiPlayerCallback, &GameMenu::menuSettingsCallback,
																&GameMenu::menuInstructionCallback, &GameMenu::menuQuitCallback };
	//按钮尺寸
	vector<float> ScaleVector = { 1, 1, 1, 1, 0.2 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(1, 1),
		Vec2(1, 1),
		Vec2(1, 0),
	};
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 100),
		Vec2(visibleSize.width + origin.x, origin.y),
	};
	/*逐个设置坐标，存入Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItem* button = MenuItemImage::create(
			"button/" + stringVector.at(i) + "-Normal.png",
			"button/" + stringVector.at(i) + "-Active.png",
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

/*菜单 初始化奖杯标签*/
void GameMenu::initTrophy()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*奖杯图标*/
	auto trophy = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("trophy.png"));
	trophy->setAnchorPoint(Vec2(0, 1));
	trophy->setPosition(Vec2(origin.x, visibleSize.height + origin.y + 10));
	trophy->setScale(0.2);
	trophy->setRotation(10);
	this->addChild(trophy, 1);

	/*奖杯数量*/
	ifstream in("trophy.txt", ios::in);
	int iTrophy;
	if (in.good())
		in >> iTrophy;
	else
		iTrophy = 0;

	auto label = Label::createWithTTF(StringUtils::format("%d", iTrophy).c_str(), "fonts/Marker Felt.ttf", 48);
	label->setAnchorPoint(Vec2(0, 1));
	label->setPosition(Vec2(origin.x + 130, visibleSize.height + origin.y - 15));
	label->setTextColor(Color4B::YELLOW);
	this->addChild(label, 1);
}

/*菜单 单人模式回调函数 切换至SelectMap*/
void GameMenu::menuSinglePlayerCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::SelectMap);
}

/*菜单 多人模式回调函数 */
void GameMenu::menuMultiPlayerCallback(cocos2d::Ref* pSender)
{
	/*暂时不实现联机模式*/
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*菜单 设置回调函数 切换至Settings*/
void GameMenu::menuSettingsCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::Settings);
}

/*菜单 游戏说明回调函数 切换至Instruction*/
void GameMenu::menuInstructionCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::Instruction);
}

/*菜单 退出游戏回调函数 √*/
void GameMenu::menuQuitCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	Director::getInstance()->end();
}