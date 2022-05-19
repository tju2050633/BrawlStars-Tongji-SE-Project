#include "cocos2d.h"
#include "Scene/SelectBrawler.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* SelectBrawler::createScene(SceneManager::AllMap map)
{
	auto scene = Scene::create();
	auto layer = SelectBrawler::create(map);
	scene->addChild(layer);
	return scene;
}

/*�Զ���create()*/
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

/*ѡӢ�۲˵�������ʼ�� ��*/
bool SelectBrawler::init(SceneManager::AllMap map)
{
	/*��ʼ������*/
	if (!Scene::init())
	{
		return false;
	}

	/*��ʼ�������Ա����*/
	_map = map;

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	/*lx
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("ѡ���ͼ��������", true);
	}*/

	/*�˵�*/
	initMenu();

	/*����*/
	SceneManager::setBGimage("BGimage3.png", this);

	return true;
}

/*ѡ��Ӣ�� ��ʼ���˵� ��*/
void SelectBrawler::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "Shelly", "Primo", "Nita", "Stu", "Back"};
	//��ť�ص�����
	vector<void (SelectBrawler::*)(Ref* pSender)> CallbackVector = {
		&SelectBrawler::menuShellyCallback,& SelectBrawler::menuPrimoCallback,
		& SelectBrawler::menuNitaCallback,& SelectBrawler::menuStuCallback,
		& SelectBrawler::menuBackCallback,
	};
	//��ť�ߴ�
	vector<float> ScaleVector = { 1,1,1,1,1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),Vec2(0.5, 0.5),
		Vec2(0, 1)
	};
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(2 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(3 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
		Vec2(4 * visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y),
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

/*ѡ��Ӣ�� ѩ��ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Shelly"��
void SelectBrawler::menuShellyCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Shelly;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*ѡ��Ӣ�� ����Ī�ص����� ��*/
void SelectBrawler::menuPrimoCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Primo;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*ѡ��Ӣ�� �����ص����� ��*/
void SelectBrawler::menuNitaCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Nita;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*ѡ��Ӣ�� ˹ͼ�ص����� ��*/
void SelectBrawler::menuStuCallback(cocos2d::Ref* pSender)
{
	SceneManager::brawler = SceneManager::AllBrawler::Stu;
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*�˵� ���ػص����� ��*/
//������SelectBrawler�л���SelectMap
void SelectBrawler::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::SelectMap);
}