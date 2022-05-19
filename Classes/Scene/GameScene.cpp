#include "cocos2d.h"
#include "Scene/GameScene.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* GameScene::createScene(SceneManager::AllMap map, SceneManager::AllBrawler brawler)
{
	auto scene = Scene::create();
	auto layer = GameScene::create( map, brawler);
	scene->addChild(layer);
	return scene;
}

/*�Զ���create()*/
GameScene* GameScene::create(SceneManager::AllMap map, SceneManager::AllBrawler brawler)
{
	auto scene = new(std::nothrow)GameScene;
	if (scene && scene->init(map, brawler))
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
bool GameScene::init(SceneManager::AllMap map, SceneManager::AllBrawler brawler)
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
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
		//audio->playBackgroundMusic("ѡ���ͼ��������", true);
	//}

	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*���ذ�ť*/
	MenuItemImage* backButton = MenuItemImage::create(
		"button/Back-Normal.png",
		"button/Back-Active.png",
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
		float x = visibleSize.width / 2;	/*���ذ�ťxֵ���ݶ�*/
		float y = visibleSize.height / 2;	/*���ذ�ťxֵ���ݶ�*/
		backButton->setPosition(Vec2(x, y));
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* gameScene = Menu::create(backButton, NULL);
	gameScene->setPosition(Vec2::ZERO);
	this->addChild(gameScene, 1);

	/*����*/
	SceneManager::setBGimage("BGimage1.png", this);

	return true;
}

/*�˵� ���ػص����� ��*/
//������GameScene�л���SelectBrawler������Ϊm_map��
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::GameMenu);
}