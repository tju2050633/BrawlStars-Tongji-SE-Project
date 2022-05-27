#include "cocos2d.h"
#include <vector>
#include <string>
#include "Scene/GameScene.h"
#include "Utils/SceneUtils.h"
#include "Player/Player.h"
#include "Player/AI.h"
#include "Brawler/Shelly.h"
#include "Brawler/Nita.h"
#include "Brawler/Primo.h"
#include "Brawler/Stu.h"
#include "Controller/PlayerController.h"

USING_NS_CC;
using namespace std;

/*获得场景对象 √*/
//init需接受参数，不能用CREATE_FUNC自动生成的create()
//用以下模板（仅需改init内参数，效果和create()一样）
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

/*游戏主场景初始化 ×*/
bool GameScene::init()
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

	/*初始化 地图、人物、两个个按钮（返回，表情）、操作器*/
	initMap();
	initBrawler();
	initLabel();
	initButton();
	initController();

	return true;
}

/*初始化 地图*/
void GameScene::initMap()
{
	TMXTiledMap* map = TMXTiledMap::create("TileGameResources/TileMap.tmx");

	this->addChild(map);
}

/*初始化 人物*/
void GameScene::initBrawler()
{
	/*创建Player*/
	_player = Player::create();
	/*绑定英雄*/
	_player->setBrawler(Shelly::create());
	_player->addChild(_player->getBrawler());
	/*英雄绑定精灵图像*/
	_player->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly.png"));
	_player->getBrawler()->setScale(0.1);
	/*设置初始位置*/
	_player->setPosition(Vec2(100, 100));


	this->addChild(_player);
}

/*初始化 标签*/
void GameScene::initLabel()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	auto label = Label::createWithTTF(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str(), "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(1, 1));
	label->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y));

	this->addChild(label);
}

/*初始化 按钮*/
void GameScene::initButton()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "Emotion", "Back" };
	//按钮回调函数
	vector<void (GameScene::*)(Ref* pSender)> CallbackVector = { &GameScene::menuEmotionCallback, &GameScene::menuBackCallback };
	//按钮尺寸
	vector<float> ScaleVector = { 1, 1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(1, 1),
		Vec2(0, 1) };
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 250),
		Vec2(origin.x, visibleSize.height + origin.y) };
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

/*初始化 操作器*/
void GameScene::initController()
{
	/*创建控制器*/
	_playerController = PlayerController::create();
	/*绑定玩家为操作器的对象*/
	_playerController->setControllerListener(_player);	


	this->addChild(_playerController);
}

/*表情 回调函数*/
void GameScene::menuEmotionCallback(cocos2d::Ref* pSender)
{
}

/*菜单 返回回调函数 √*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}