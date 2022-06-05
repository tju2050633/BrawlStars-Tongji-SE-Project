#include "cocos2d.h"
#include "Scene/OpeningAnimation.h"
#include "Utils/SceneUtils.h"
#include "Scene/GameMenu.h"
#include "Utils/AnimationUtils.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*获得场景对象 √*/
Scene* OpeningAnimation::createScene()
{
	auto scene = Scene::create();
	auto layer = OpeningAnimation::create();
	scene->addChild(layer);
	return scene;
}

/*开场动画场景初始化 ×*/
bool OpeningAnimation::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	/*三秒后进入菜单界面*/    //改为2秒
	scheduleOnce(SEL_SCHEDULE(&OpeningAnimation::EnterMenu), 1.5f); 

	/*预加载所有图片、音频等资源*/
	PreloadResource();

	/*背景*/
	SceneUtils::setBGimage("OpeningAnimation.png", this, SceneUtils::setBGimageWith::SpriteFrameCache);

	return true;
}

/*预加载所有图片、音频等资源*/
void OpeningAnimation::PreloadResource()
{
	/*音乐音效*/
	SimpleAudioEngine::getInstance()->preloadEffect("Music/ButtonEffect.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Combat.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Defeat.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Final.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Menu.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Victory.mp3");
	/*精灵图*/
	Director::getInstance()->getTextureCache()->addImage("trophy.png");
	Director::getInstance()->getTextureCache()->addImage("hpBar.png");
	Director::getInstance()->getTextureCache()->addImage("ammoBar.png");
	Director::getInstance()->getTextureCache()->addImage("energyBar.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Shelly-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Nita-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Primo-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("Portrait/Stu-Normal.png");
	Director::getInstance()->getTextureCache()->addImage("Animation/Shelly_Bullet.png");
	Director::getInstance()->getTextureCache()->addImage("Animation/Nita_Bullet.png");
	Director::getInstance()->getTextureCache()->addImage("Animation/Primo_Bullet1.png");
	Director::getInstance()->getTextureCache()->addImage("Animation/Primo_Bullet2.png");
	Director::getInstance()->getTextureCache()->addImage("Animation/Primo_Bullet3.png");
	Director::getInstance()->getTextureCache()->addImage("Animation/Primo_Bullet4.png");
	Director::getInstance()->getTextureCache()->addImage("Animation/Stu_Bullet.png");
	/*雪莉*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Shelly/Shelly_Angry.png");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Shelly/Shelly_Attack.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Shelly/Shelly_Start.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Shelly/Shelly_Kill.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Shelly/Shelly_Ult.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Shelly/Shelly_Hurt.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Shelly/Shelly_Die.mp3");
	/*妮塔*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Nita/Nita_Angry.png");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Nita/Nita_Attack.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Nita/Nita_Start.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Nita/Nita_Kill.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Nita/Nita_Ult.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Nita/Nita_Hurt.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Nita/Nita_Die.mp3");
	/*普里莫*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Primo/Primo_Angry.png");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Primo/Primo_Attack.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Primo/Primo_Start.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Primo/Primo_Kill.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Primo/Primo_Ult.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Primo/Primo_Hurt.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Primo/Primo_Die.mp3");
	/*斯图*/
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Neutral.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Happy.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_GG.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Sad.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Thanks.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Phew.png");
	Director::getInstance()->getTextureCache()->addImage("Emotion/Stu/Stu_Angry.png");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Stu/Stu_Attack.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Stu/Stu_Start.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Stu/Stu_Kill.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Stu/Stu_Ult.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Stu/Stu_Hurt.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Stu/Stu_Die.mp3");

	/*后续背景图*/
	Director::getInstance()->getTextureCache()->addImage("BGimage/GameMenu.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectMap.png");
	Director::getInstance()->getTextureCache()->addImage("BGimage/SelectBrawler.png");
	/*加载背景图plist*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BGimage/BGimage.plist");
	/*加载控制器plist*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/Controller.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/AttackButton.plist");
	/*加载动画帧plist*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Shelly.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Nita.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Primo.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Primo_quan.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/Stu.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Animation/bear.plist");
}

/*切换到游戏菜单*/
void OpeningAnimation::EnterMenu(float dt)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);

	if(SceneUtils::_musicOn)
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Menu.mp3", true);
}
