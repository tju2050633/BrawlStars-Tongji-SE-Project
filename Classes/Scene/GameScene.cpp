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

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

/*��Ϸ��������ʼ�� ��*/
bool GameScene::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
	//audio->playBackgroundMusic("ѡ���ͼ��������", true);
	//}

	/*��ʼ�� ��ͼ�������������ť�����أ����飩��������*/
	initMap();
	initBrawler();
	initLabel();
	initButton();
	initController();

	return true;
}

/*��ʼ�� ��ͼ*/
void GameScene::initMap()
{
	TMXTiledMap* map = TMXTiledMap::create("TileGameResources/TileMap.tmx");

	this->addChild(map);
}

/*��ʼ�� ����*/
void GameScene::initBrawler()
{
	/*����Player*/
	_player = Player::create();
	/*��Ӣ��*/
	_player->setBrawler(Shelly::create());
	_player->addChild(_player->getBrawler());
	/*Ӣ�۰󶨾���ͼ��*/
	_player->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly.png"));
	_player->getBrawler()->setScale(0.1);
	/*���ó�ʼλ��*/
	_player->setPosition(Vec2(100, 100));


	this->addChild(_player);
}

/*��ʼ�� ��ǩ*/
void GameScene::initLabel()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	auto label = Label::createWithTTF(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str(), "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(1, 1));
	label->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y));

	this->addChild(label);
}

/*��ʼ�� ��ť*/
void GameScene::initButton()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "Emotion", "Back" };
	//��ť�ص�����
	vector<void (GameScene::*)(Ref* pSender)> CallbackVector = { &GameScene::menuEmotionCallback, &GameScene::menuBackCallback };
	//��ť�ߴ�
	vector<float> ScaleVector = { 1, 1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(1, 1),
		Vec2(0, 1) };
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 250),
		Vec2(origin.x, visibleSize.height + origin.y) };
	/*����������꣬����Vector*/
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

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*��ʼ�� ������*/
void GameScene::initController()
{
	/*����������*/
	_playerController = PlayerController::create();
	/*�����Ϊ�������Ķ���*/
	_playerController->setControllerListener(_player);	


	this->addChild(_playerController);
}

/*���� �ص�����*/
void GameScene::menuEmotionCallback(cocos2d::Ref* pSender)
{
}

/*�˵� ���ػص����� ��*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}