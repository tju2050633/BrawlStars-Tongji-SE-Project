#include <vector>
#include <string>
#include "cocos2d.h"
#include "Scene/SelectMap.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
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
	if (!Scene::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("ѡ���ͼ��������", true);
	}

	/*�˵�*/
	initMenu();

	/*����*/
	SceneManager::setBGimage("BGimage2.png", this);

	return true;
}

/*ѡ���ͼ ��ʼ���˵� ��*/
void SelectMap::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "MapA", "MapB", "MapC", "Back" };
	//��ť�ص�����
	vector<void (SelectMap::*)(Ref* pSender)> CallbackVector = {
		&SelectMap::menuMapACallback,&SelectMap::menuMapBCallback,
		&SelectMap::menuMapCCallback,&SelectMap::menuBackCallback
	};
	//��ť�ߴ�
	vector<float> ScaleVector = { 0.2 ,0.15,0.1,1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),Vec2(0, 1)
	};
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 2 * visibleSize.height / 4 + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 4 + origin.y),
		Vec2(origin.x, visibleSize.height + origin.y)
	};
	/*���������ť��������Ϣ������Vector*/
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

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*ѡ���ͼ ��ͼA�ص����� ��*/
void SelectMap::menuMapACallback(cocos2d::Ref* pSender)
{
	SceneManager::map = SceneManager::AllMap::MapA;
	SceneManager::getInstance()->changeScene(SceneManager::SelectBrawler);
}

/*ѡ���ͼ ��ͼB�ص����� ��*/
void SelectMap::menuMapBCallback(cocos2d::Ref* pSender)
{
	SceneManager::map = SceneManager::AllMap::MapB;
	SceneManager::getInstance()->changeScene(SceneManager::SelectBrawler);
}

/*ѡ���ͼ ��ͼC�ص����� ��*/
void SelectMap::menuMapCCallback(cocos2d::Ref* pSender)
{
	SceneManager::map = SceneManager::AllMap::MapC;
	SceneManager::getInstance()->changeScene(SceneManager::SelectBrawler);
}

/*ѡ���ͼ ���ػص����� ��*/
//������SelectMap�л���GameMenu
void SelectMap::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::GameMenu);
}