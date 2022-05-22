#include "cocos2d.h"
#include <vector>
#include <string>
#include "Scene/SelectBrawler.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;
using namespace std;

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* SelectBrawler::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectBrawler::create();
	scene->addChild(layer);
	return scene;
}

/*ѡӢ�۲˵�������ʼ�� ��*/
bool SelectBrawler::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	/*lx
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("ѡ���ͼ��������", true);
	}*/

	/*�˵�*/
	initMenu();

	/*����*/
	SceneUtils::setBGimage("BGimage/SelectBrawler.png", this);

	return true;
}

/*ѡ��Ӣ�� ��ʼ���˵� ��*/
void SelectBrawler::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "Shelly", "Primo", "Nita", "Stu", "Back" };
	//��ť�ص�����
	vector<void (SelectBrawler::*)(Ref* pSender)> CallbackVector = {
		&SelectBrawler::menuShellyCallback,
		&SelectBrawler::menuPrimoCallback,
		&SelectBrawler::menuNitaCallback,
		&SelectBrawler::menuStuCallback,
		&SelectBrawler::menuBackCallback };
	//��ť�ߴ�
	vector<float> ScaleVector = { 1, 1, 1, 1, 1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0, 1) };
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(2 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(3 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(4 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(origin.x, visibleSize.height + origin.y) };
	/*���������ť��������Ϣ������Vector*/
	for (ssize_t i = 0; i < stringVector.size(); i++)
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

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*ѡ��Ӣ�� ѩ��ص����� ��*/
void SelectBrawler::menuShellyCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_brawler = SceneUtils::AllBrawler::Shelly;
	SceneUtils::changeScene(SceneUtils::GameScene);
}

/*ѡ��Ӣ�� ����Ī�ص����� ��*/
void SelectBrawler::menuPrimoCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_brawler = SceneUtils::AllBrawler::Primo;
	SceneUtils::changeScene(SceneUtils::GameScene);
}

/*ѡ��Ӣ�� �����ص����� ��*/
void SelectBrawler::menuNitaCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_brawler = SceneUtils::AllBrawler::Nita;
	SceneUtils::changeScene(SceneUtils::GameScene);
}

/*ѡ��Ӣ�� ˹ͼ�ص����� ��*/
void SelectBrawler::menuStuCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_brawler = SceneUtils::AllBrawler::Stu;
	SceneUtils::changeScene(SceneUtils::GameScene);
}

/*�˵� ���ػص����� ��*/
//������SelectBrawler�л���SelectMap
void SelectBrawler::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::SelectMap);
}