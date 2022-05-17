#include "cocos2d.h"
#include "Scene/SelectBrawler.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneInfo.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* SelectBrawler::createScene(std::string map)
{
	auto scene = Scene::create();
	auto layer = SelectBrawler::create(map);
	scene->addChild(layer);
	return scene;
}

/*�Զ���create()*/
SelectBrawler* SelectBrawler::create(std::string map)
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

/*�������� ��*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

/*ѡӢ�۲˵�������ʼ�� ��*/
bool SelectBrawler::init(std::string map)
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
	initBG();

	return true;
}

/*ѡ��Ӣ�� ��ʼ���˵� ��*/
void SelectBrawler::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*ѩ��*/
	MenuItemImage* ShellyButton = MenuItemImage::create(
		"ѩ��-Normal.png",
		"ѩ��-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuShellyCallback, this)
	);
	if (ShellyButton == nullptr ||
		ShellyButton->getContentSize().width <= 0 ||
		ShellyButton->getContentSize().height <= 0)
	{
		problemLoading("'ѩ��'");
	}
	else
	{
		float x = visibleSize.width / 2;/*ѩ�� xֵ,�ݶ�*/
		float y = visibleSize.height / 2;/*ѩ�� yֵ,�ݶ�*/
		ShellyButton->setPosition(Vec2(x, y));
	}

	/*����Ī*/
	MenuItemImage* PrimoButton = MenuItemImage::create(
		"����Ī-Normal.png",
		"����Ī-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuPrimoCallback, this)
	);
	if (PrimoButton == nullptr ||
		PrimoButton->getContentSize().width <= 0 ||
		PrimoButton->getContentSize().height <= 0)
	{
		problemLoading("'����Ī'");
	}
	else
	{
		float x = visibleSize.width / 2;/*����Ī xֵ,�ݶ�*/
		float y = visibleSize.height / 2;/*����Ī yֵ,�ݶ�*/
		PrimoButton->setPosition(Vec2(x, y));
	}

	/*����*/
	MenuItemImage* NitaButton = MenuItemImage::create(
		"����-Normal.png",
		"����-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuNitaCallback, this)
	);
	if (NitaButton == nullptr ||
		NitaButton->getContentSize().width <= 0 ||
		NitaButton->getContentSize().height <= 0)
	{
		problemLoading("'����'");
	}
	else
	{
		float x = visibleSize.width / 2;/*���� xֵ,�ݶ�*/
		float y = visibleSize.height / 2;/*���� yֵ,�ݶ�*/
		NitaButton->setPosition(Vec2(x, y));
	}

	/*˹ͼ*/
	MenuItemImage* StuButton = MenuItemImage::create(
		"˹ͼ-Normal.png",
		"˹ͼ-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuSituCallback, this)
	);
	if (StuButton == nullptr ||
		StuButton->getContentSize().width <= 0 ||
		StuButton->getContentSize().height <= 0)
	{
		problemLoading("'˹ͼ'");
	}
	else
	{
		float x = visibleSize.width / 2;/*˹ͼ xֵ,�ݶ�*/
		float y = visibleSize.height / 2;/*˹ͼ yֵ,�ݶ�*/
		StuButton->setPosition(Vec2(x, y));
	}

	/*���ذ�ť*/
	MenuItemImage* backButton = MenuItemImage::create(
		"���ذ�ť-Normal.png",
		"���ذ�ť-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuBackCallback, this)
	);
	if (backButton == nullptr ||
		backButton->getContentSize().width <= 0 ||
		backButton->getContentSize().height <= 0)
	{
		problemLoading("'���ذ�ť'");
	}
	else
	{
		float x = visibleSize.width / 2;/*���ذ�ť xֵ,�ݶ�*/
		float y = visibleSize.height / 2;/*���ذ�ť yֵ,�ݶ�*/
		backButton->setPosition(Vec2(x, y));
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* selectBrawler = Menu::create(ShellyButton, PrimoButton, NitaButton, StuButton, backButton, NULL);
	selectBrawler->setPosition(Vec2::ZERO);
	this->addChild(selectBrawler, 1);
}

/*ѡ��Ӣ�� ��ʼ������ ��*/
void SelectBrawler::initBG()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	auto background = Sprite::create("ѡ��Ӣ�۱���ͼƬ");
	if (background == nullptr)
	{
		problemLoading("'ѡ��Ӣ�۱���ͼƬ'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}
}

/*ѡ��Ӣ�� ѩ��ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Shelly"��
void SelectBrawler::menuShellyCallback(cocos2d::Ref* pSender)
{
	SceneInfo::brawler = "Shelly";
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*ѡ��Ӣ�� ����Ī�ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Primo"��
void SelectBrawler::menuPrimoCallback(cocos2d::Ref* pSender)
{
	SceneInfo::brawler = "Primo";
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*ѡ��Ӣ�� �����ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Nita"��
void SelectBrawler::menuNitaCallback(cocos2d::Ref* pSender)
{
	SceneInfo::brawler = "Nita";
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*ѡ��Ӣ�� ˹ͼ�ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Situ"��
void SelectBrawler::menuSituCallback(cocos2d::Ref* pSender)
{
	SceneInfo::brawler = "Stu";
	SceneManager::getInstance()->changeScene(SceneManager::GameScene);
}

/*�˵� ���ػص����� ��*/
//������SelectBrawler�л���SelectMap
void SelectBrawler::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::SelectMap);
}