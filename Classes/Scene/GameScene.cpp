#include "cocos2d.h"
#include "Scene/GameScene.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene *GameScene::createScene()
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
	if (!Scene::init())
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
	initControler();

	return true;
}

/*��ʼ�� ��ͼ*/
void initMap()
{
}

/*��ʼ�� ����*/
void initBrawler()
{
}

/*��ʼ�� ��ǩ*/
void initLabel()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	auto label = Label::createWithTTF(StringUtils::format("ʣ��Ӣ�ۣ�%d", SceneManager::brawler_number), "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(1, 1));
	button->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y));

	this->addChild(label, 10);
}

/*��ʼ�� ��ť*/
void initButton()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem *> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = {"Emotion", "Back"};
	//��ť�ص�����
	vector<void (GameScene::*)(Ref * pSender)> CallbackVector = {&GameScene::menuEmotionCallback, &GameScene::menuBackCallback};
	//��ť�ߴ�
	vector<float> ScaleVector = {1, 1};
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(1, 1),
		Vec2(0, 1)};
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 250),
		Vec2(origin.x, visibleSize.height + origin.y)};
	/*����������꣬����Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItem *button = MenuItemImage::create(
			StringUtils::format("button/%s-Normal.png", stringVector[i]),
			StringUtils::format("button/%s-Active.png", stringVector[i]),
			bind(CallbackVector[i], this, std::placeholders::_1));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneManager::problemLoading(stringVector[i]);
		else
		{
			button->setScale(ScaleVector[i]);
			button->setAnchorPoint(AnchorVector[i]);
			button->setPosition(PositionVector[i]);
		}
		MenuItemVector.pushBack(button);
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu *menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*��ʼ�� ������*/
void initControler()
{
}

/*���� �ص�����*/
void menuEmotionCallback(cocos2d::Ref *pSender)
{
}

/*�˵� ���ػص����� ��*/
void GameScene::menuBackCallback(cocos2d::Ref *pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::GameMenu);
}