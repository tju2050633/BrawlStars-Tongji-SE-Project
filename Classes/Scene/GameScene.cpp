#include "cocos2d.h"
#include "GameScene.h"
#include "SelectBrawler.h"
#include "SelectMap.h"

USING_NS_CC;

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* GameScene::createScene(std::string map, std::string brawler)
{
	return GameScene::create(std::string map, std::string brawler);
}

/*�Զ���create()*/
GameScene* GameScene::create(std::string map, std::string brawler)
{
	auto scene = new(std::nothrow)GameScene;
	if (scene && scene->init(map, std::string brawler))
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

/*��Ϸ��������ʼ�� ��*/
bool GameScene::init(std::string map, std::string brawler)
{
	/*��ʼ������*/
	if (!Scene::init())
	{
		return false;
	}

	/*��ʼ�������Ա����*/
	m_map = map;
	m_brawler = brawler;

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("ѡ���ͼ��������", true);
	}

	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*���ذ�ť*/
	MenuItemImage* backButton = MenuItemImage::create(
		"button/Return.png",
		"button/Return-Active.png",
		CC_CALLBACK_1(GameScene::menuBackCallback, this)
	);
	if (backButton == nullptr ||
		backButton->getContentSize().width <= 0 ||
		backButton->getContentSize().height <= 0)
	{
		problemLoading("'���ذ�ť'");
	}
	else
	{
		float x = /*���ذ�ť xֵ*/;
		float y = /*���ذ�ť yֵ*/;
		backButton->setPosition(Vec2(x, y));
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* selectMap = Menu::create(backButton, NULL);
	selectMap->setPosition(Vec2::ZERO);
	this->addChild(selectMap, 1);

	/*����*/
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

	return true;
}

/*�˵� ���ػص����� ��*/
//������GameScene�л���SelectBrawler������Ϊm_map��
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = SelectMap::create(m_map);
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}