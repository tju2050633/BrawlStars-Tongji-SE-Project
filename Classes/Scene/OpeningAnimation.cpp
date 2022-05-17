#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/SceneManager.h"
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

	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*����������һЩ��ʱ����*/
	float x = visibleSize.width / 2 + origin.x;
	float y = visibleSize.height / 2 + origin.y;
	auto StartSprite = Sprite::create("Bnt_settings.png");
	StartSprite->setPosition(Vec2(x, y));
	this->addChild(StartSprite);

	TransitionScene* reScene = NULL;
	Scene* s = Scene::create();

	float t = 2.2f;
	reScene = TransitionJumpZoom::create(t, s);

	this->addChild(reScene);
	auto TransSprite = Sprite::create("HelloWorld.png");
	TransSprite->setPosition(Vec2(x, y));
	s->addChild(TransSprite);

	SceneManager::getInstance()->changeScene(SceneManager::GameMenu);
	return true;
}