#include "cocos2d.h"
#include <vector>
#include <string>
#include "Room.h"
#include "Utils/SceneUtils.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

/*获得场景对象 √*/
Scene* Room::createScene()
{
	auto scene = Scene::create();
	auto layer = Room::create();
	scene->addChild(layer);
	return scene;
}

/*选英雄菜单场景初始化 ×*/
bool Room::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	/*初始化场景信息——英雄数量*/
	SceneUtils::_brawlerNumber = 0;
	SceneUtils::_shellyNumber = 0;
	SceneUtils::_nitaNumber = 0;
	SceneUtils::_primoNumber = 0;
	SceneUtils::_stuNumber = 0;
	
	/*菜单*/
	initMenu();

	/*标签*/
	initLabel();

	/*玩家英雄头像*/
	addPortrait(SceneUtils::_brawler);	//添加玩家头像
	SceneUtils::_brawlerNumber++;

	/*背景*/
	SceneUtils::setBGimage("BGimage/Background.png", this, SceneUtils::setBGimageWith::TextureCache);

	return true;
}

/*菜单初始化*/
void Room::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "Start", "Shelly", "Primo", "Nita", "Stu", "Back"};
	//按钮回调函数
	vector<void (Room::*)(Ref* pSender)> CallbackVector = {
		&Room::menuStartCallback,
		& Room::menuAddShellyCallback,
		& Room::menuAddPrimoCallback,
		& Room::menuAddNitaCallback,
		& Room::menuAddStuCallback,
		& Room::menuBackCallback };
	//按钮尺寸
	vector<float> ScaleVector = { 1, 0.2, 0.2, 0.2, 0.2, 1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0, 1) };
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 10 + origin.y),
		Vec2(5 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(6.33 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(7.66 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(9 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
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

/*标签初始化*/
void Room::initLabel()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//Label的文本
	vector<string> stringVector = { "Player", "AI #1", "AI #2", "AI #3", "AI #4", "AI #5","AI #6", "AI #7", "AI #8", "AI #9", "Add AI brawler:" };
	//Label坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 50),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 130),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 210),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 290),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 370),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 50),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 130),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 210),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 290),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 370),
		Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y), };

	/*逐个创建Label*/
	for (ssize_t i = 0; i < stringVector.size(); i++)
	{
		_labels.pushBack(Label::createWithTTF(stringVector.at(i), "fonts/arial.ttf", 48));
		_labels.at(i)->setPosition(PositionVector.at(i));
		this->addChild(_labels.at(i), 1);
	}

	/*AI #1~9先隐藏*/
	for (int i = 1; i <= 9; i++)
	{
		_labels.at(i)->setVisible(false);
	}
}

/*添加英雄头像*/
void Room::addPortrait(SceneUtils::AllBrawler brawler)
{
	/*获取对应英雄图像*/
	Sprite* portrait;
	switch (brawler)
	{
	case SceneUtils::Shelly:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Shelly-Normal.png"));
		break;
	case SceneUtils::Primo:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Primo-Normal.png"));
		break;
	case SceneUtils::Nita:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Nita-Normal.png"));
		break;
	case SceneUtils::Stu:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Stu-Normal.png"));
		break;
	default:
		break;
	}
	portrait->setScale(0.2);

	/*计算位置，放置图像，对应标签可见*/
	INT32 index = SceneUtils::_brawlerNumber;
	portrait->setPosition(_labels.at(index)->getPosition() + Vec2(150, 0));
	_labels.at(index)->setVisible(true);
	
	this->addChild(portrait, 1);
}

/*开始 回调函数*/
void Room::menuStartCallback(Ref* pSender)
{
	if(SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");

	//英雄数需>=2
	if (SceneUtils::_brawlerNumber == 1)
		return;

	if (SceneUtils::_musicOn)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Combat.mp3", true);
	}
	SceneUtils::changeScene(SceneUtils::GameScene);
}

/*添加Shelly 回调函数*/
void Room::menuAddShellyCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Shelly);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_shellyNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*添加Nita 回调函数*/
void Room::menuAddNitaCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Nita);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_nitaNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*添加Primo 回调函数*/
void Room::menuAddPrimoCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Primo);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_primoNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*添加Stu 回调函数*/
void Room::menuAddStuCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Stu);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_stuNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*返回SelectBrawler*/
void Room::menuBackCallback(Ref* pSender)
{
	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::SelectBrawler);
}