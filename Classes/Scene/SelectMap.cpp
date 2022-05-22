#include <string>
#include "cocos2d.h"
#include "Scene/SelectMap.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;
using namespace std;

/*��ó������� ��*/
Scene* SelectMap::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectMap::create();
	scene->addChild(layer);
	return scene;
}

/*ѡ���ͼ ������ʼ�� ��*/
bool SelectMap::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	// auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// if (!audio->isBackgroundMusicPlaying())
	// {
	// 	audio->playBackgroundMusic("ѡ���ͼ��������", true);
	// }

	/*�˵�*/
	initMenu();

	/*����*/
	SceneUtils::setBGimage("BGimage/SelectMap", this);

	return true;
}

/*ѡ���ͼ ��ʼ���˵� ��*/
void SelectMap::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "MapA", "MapB", "MapC", "Back" };
	//��ť�ص�����
	vector<void (SelectMap::*)(Ref* pSender)> CallbackVector = {
		&SelectMap::menuMapACallback, &SelectMap::menuMapBCallback,
		&SelectMap::menuMapCCallback, &SelectMap::menuBackCallback };
	//��ť�ߴ�
	vector<float> ScaleVector = { 0.2, 0.15, 0.1, 1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0, 1) };
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 2 * visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 4 + origin.y),
		Vec2(origin.x, visibleSize.height + origin.y) };
	/*���������ť��������Ϣ������Vector*/
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

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*ѡ���ͼ ��ͼA�ص����� ��*/
void SelectMap::menuMapACallback(cocos2d::Ref* pSender)
{
	SceneUtils::_map = SceneUtils::AllMap::MapA;
	SceneUtils::changeScene(SceneUtils::SelectBrawler);
}

/*ѡ���ͼ ��ͼB�ص����� ��*/
void SelectMap::menuMapBCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_map = SceneUtils::AllMap::MapB;
	SceneUtils::changeScene(SceneUtils::SelectBrawler);
}

/*ѡ���ͼ ��ͼC�ص����� ��*/
void SelectMap::menuMapCCallback(cocos2d::Ref* pSender)
{
	SceneUtils::_map = SceneUtils::AllMap::MapC;
	SceneUtils::changeScene(SceneUtils::SelectBrawler);
}

/*ѡ���ͼ ���ػص����� ��*/
//������SelectMap�л���GameMenu
void SelectMap::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::GameMenu);
}