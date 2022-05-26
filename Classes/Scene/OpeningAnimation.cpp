#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Utils/SceneUtils.h"
#include "Scene/GameMenu.h"

USING_NS_CC;

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
	if (!Layer::init())
	{
		return false;
	}

	/*��������˵�����*/
	scheduleOnce(SEL_SCHEDULE(&OpeningAnimation::EnterMenu), 3.0f);

	/*����*/
	// auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// if (!audio->isBackgroundMusicPlaying()) {
	// 	audio->playBackgroundMusic("������������", true);
	// }

	/*����*/
	SceneUtils::setBGimage("BGimage/OpeningAnimation.png", this);

	/*��ӭͼ��*/
	LoadWelcomeLabel();

	/*Ԥ��������ͼƬ����Ƶ����Դ*/
	PreloadResource();

	return true;
}

/*���ػ�ӭͼ��*/
void OpeningAnimation::LoadWelcomeLabel()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	auto welcome = Sprite::create("BGimage/Welcome.png");

	if (welcome == nullptr)
	{
		SceneUtils::problemLoading("'BGimage/Welcome.png'");
	}
	else
	{
		welcome->setScale(0.3);
		welcome->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 75));
		this->addChild(welcome, 1);
	}
}

/*Ԥ��������ͼƬ����Ƶ����Դ*/
void OpeningAnimation::PreloadResource()
{
	/*��������ͼ*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	/*�˵���ť*/
	Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/Settings-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/Settings-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/Instruction-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/Instruction-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/Quit-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/Quit-Active.png");
	/*��ͼ��ť*/
	Director::getInstance()->getTextureCache()->addImage("button/MapA-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapA-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Active.png");
}

/*�л�����Ϸ�˵�*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}