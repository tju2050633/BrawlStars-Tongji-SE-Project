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

	/*����*/
	// auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// if (!audio->isBackgroundMusicPlaying()) {
	// 	audio->playBackgroundMusic("������������", true);
	// }

	/*Ԥ��������ͼƬ����Ƶ����Դ*/
	PreloadResource();

	/*����*/
	SceneUtils::setBGimage("OpeningAnimation.png", this, 2);

	return true;
}

/*Ԥ��������ͼƬ����Ƶ����Դ*/
void OpeningAnimation::PreloadResource()
{
	/*��������ͼ*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	///*�˵���ť*/
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("button.plist");
	//Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/SinglePlayer-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/MultiPlayer-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Settings-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Settings-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Instruction-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Instruction-Active.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Quit-Normal.png");
	//Director::getInstance()->getTextureCache()->addImage("button/Quit-Active.png");
	/*��ͼ��ť*/
	/*Director::getInstance()->getTextureCache()->addImage("button/MapA-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapA-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapB-Active.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("button/MapC-Active.png");*/

	Director::getInstance()->getTextureCache()->addImageAsync("BGimage/BGimage.plist", CC_CALLBACK_1(OpeningAnimation::plistImageAsyncCallback, this));
}

/*�л�����Ϸ�˵�*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

void OpeningAnimation::plistImageAsyncCallback(Texture2D* texture) {
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("BGimage/BGimage.plist", texture);
}