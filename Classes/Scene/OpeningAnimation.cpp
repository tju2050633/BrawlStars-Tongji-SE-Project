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

	/*��������˵�����*/    //��Ϊ2��
	scheduleOnce(SEL_SCHEDULE(&OpeningAnimation::EnterMenu), 1.5f);   // why 1s ��

	/*Ԥ��������ͼƬ����Ƶ����Դ*/
	PreloadResource();

	/*����*/
	SceneUtils::setBGimage("OpeningAnimation.png", this, SceneUtils::setBGimageWith::SpriteFrameCache);

	return true;
}

/*Ԥ��������ͼƬ����Ƶ����Դ*/
void OpeningAnimation::PreloadResource()
{
	/*����ͼ*/
	Director::getInstance()->getTextureCache()->addImage("trophy.png");
	/*��������ͼ*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	/*���ر���ͼplist*/
	Director::getInstance()->getTextureCache()->addImageAsync("BGimage/BGimage.plist", CC_CALLBACK_1(OpeningAnimation::plistImageAsyncCallback, this));
	/*���ؿ�����plist*/
	Director::getInstance()->getTextureCache()->addImageAsync("Controller/Controller.plist", CC_CALLBACK_1(OpeningAnimation::plistControllerAsyncCallback, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Controller/AttackButton.plist", CC_CALLBACK_1(OpeningAnimation::plistAttackAsyncCallback, this));
	/*���ض���֡plist*/
}

/*�л�����Ϸ�˵�*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

void OpeningAnimation::plistImageAsyncCallback(Texture2D* texture) 
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("BGimage/BGimage.plist", texture);
}

void OpeningAnimation::plistControllerAsyncCallback(Texture2D* texture)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Controller/Controller.plist");
}

void OpeningAnimation::plistAttackAsyncCallback(Texture2D* texture)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Controller/AttackButton.plist");
}