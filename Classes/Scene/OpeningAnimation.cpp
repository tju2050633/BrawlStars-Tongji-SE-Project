#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Utils/SceneUtils.h"
#include "Scene/GameMenu.h"
#include "Utils/AnimationUtils.h"
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
	/*������Ч*/
	SimpleAudioEngine::getInstance()->preloadEffect("Music/ButtonEffect.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Combat.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Defeat.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Final.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Menu.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Victory.mp3");
	/*����ͼ*/
	Director::getInstance()->getTextureCache()->addImage("trophy.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Shelly-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Nita-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Primo-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Stu-Normal.png");
	/*ѩ��*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Angry.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Shelly/Shelly_Start.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Shelly/Shelly_Kill.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Shelly/Shelly_Ult.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Shelly/Shelly_Hurt.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Shelly/Shelly_Die.png");
	/*����*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Angry.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Nita/Nita_Start.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Nita/Nita_Kill.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Nita/Nita_Ult.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Nita/Nita_Hurt.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Nita/Nita_Die.png");
	/*����Ī*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Angry.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Primo/Primo_Start.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Primo/Primo_Kill.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Primo/Primo_Ult.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Primo/Primo_Hurt.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Primo/Primo_Die.png");
	/*˹ͼ*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Angry.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Stu/Stu_Start.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Stu/Stu_Kill.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Stu/Stu_Ult.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Stu/Stu_Hurt.png");
	Director::getInstance()->getTextureCache()->addImage("Music/Stu/Stu_Die.png");

	/*��������ͼ*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	/*���ر���ͼplist*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BGimage/BGimage.plist");
	/*���ؿ�����plist*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/Controller.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/AttackButton.plist");
	/*���ض���֡plist*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Nita.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Primo.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Stu.plist");
}

/*�л�����Ϸ�˵�*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Menu.mp3", true);
}
