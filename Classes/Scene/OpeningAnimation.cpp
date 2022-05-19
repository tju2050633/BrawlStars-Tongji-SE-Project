#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/SceneManager.h"
#include "Scene/GameMenu.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*��ó������� ��*/
Scene* OpeningAnimation::createScene()
{
	auto scene = Scene::create();
	auto layer = OpeningAnimation::create();
	scene->addChild(layer);
	return scene;
}

/*��������������ʼ�� ��*/
bool OpeningAnimation::init()
{
	/*��ʼ������*/
	if (!Scene::init())
	{
		return false;
	}

	/*����*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("ѡ���ͼ��������", true);
	}

	/*����*/
	SceneManager::setBGimage("BGimage1.png", this);

	/*���ػ�ӭͼ��*/
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	auto welcome = Sprite::create("Welcome.png");
	welcome->setScale(0.3);

	if (welcome == nullptr)
	{
		SceneManager::problemLoading("'Welcome.png'");
	}
	else
	{
		welcome->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 75));
		this->addChild(welcome, 1);
	}

	/*��������˵�����*/
	scheduleOnce(schedule_selector(OpeningAnimation::EnterMenu), 3.0f);
	
	return true;
}

void OpeningAnimation::EnterMenu(float dt)
{
	SceneManager::changeScene(SceneManager::GameMenu);
}
