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

	/*��������˵�����*/
	scheduleOnce(schedule_selector(OpeningAnimation::EnterMenu), 3.0f);

	/*����*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("������������", true);
	}

	/*����*/
	SceneManager::setBGimage("BGimage1.png", this);

	/*��ӭͼ��*/
	LoadWelcomeLabel();

	/*Ԥ��������ͼƬ����Ƶ����Դ*/
	PreloadResource();

	return true;
}

/*���ػ�ӭͼ��*/
void LoadWelcomeLabel()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	auto welcome = Sprite::create("Welcome.png");
	
	if (welcome == nullptr)
	{
		SceneManager::problemLoading("'Welcome.png'");
	}
	else
	{
		welcome->setScale(0.3);
		welcome->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 75));
		this->addChild(welcome, 1);
	}
}

/*Ԥ��������ͼƬ����Ƶ����Դ*/
void PreloadResource()
{
	/*��������ͼ*/
	TextureCache::getInstance()->addImageAsync("BGimage2.png");
	TextureCache::getInstance()->addImageAsync("BGimage3.png");
	/*��ťͼƬ*/
	TextureCache::getInstance()->addImageAsync("button/SinglePlayer-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/SinglePlayer-Active.png");
	TextureCache::getInstance()->addImageAsync("button/MultiPlayer-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MultiPlayer-Active.png");
	TextureCache::getInstance()->addImageAsync("button/Settings-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/Settings-Active.png");
	TextureCache::getInstance()->addImageAsync("button/Instruction-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/Instruction-Active.png");
	TextureCache::getInstance()->addImageAsync("button/Quit-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/Quit-Active.png");
	/*ѡ���ͼͼƬ*/
	TextureCache::getInstance()->addImageAsync("button/MapA-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MapA-Active.png");
	TextureCache::getInstance()->addImageAsync("button/MapB-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MapB-Active.png");
	TextureCache::getInstance()->addImageAsync("button/MapC-Normal.png");
	TextureCache::getInstance()->addImageAsync("button/MapC-Active.png");
}

/*�л�����Ϸ�˵�*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneManager::changeScene(SceneManager::GameMenu);
}
