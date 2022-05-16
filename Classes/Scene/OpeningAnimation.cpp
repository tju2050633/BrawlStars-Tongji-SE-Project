#include "cocos2d.h"
#include "OpeningAnimation.h"
#include "GameMenu.h"
#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

/*��ó������� ��*/
Scene* OpeningAnimation::createScene()
{
	//lx
	//create a scene object
	auto scene = Scene::create();
	//create OpeningAnimation object
	auto layer = OpeningAnimation::create();
	//add the object obove to the scene
	scene->addChild(layer);
	return scene;
	//return OpeningAnimation::create();
}

/*��������������ʼ�� ��*/
bool OpeningAnimation::init()
{
	/*��ʼ������*/
	if (!Scene::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
		//audio->playBackgroundMusic("ѡ���ͼ��������", true);
	//}
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�
	float x = visibleSize.width / 2 + origin.x;
	float y = visibleSize.height / 2 + origin.y;
	auto StartSprite = Sprite::create("button/mainSetting.jpg");
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

	//replaceWithScene(MenuScene);
	return true;
}