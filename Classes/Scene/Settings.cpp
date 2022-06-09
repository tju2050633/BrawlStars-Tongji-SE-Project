#include "cocos2d.h"
#include <string>
#include "ui/UIText.h"
#include "Settings.h"
#include "GameMenu.h"
#include "Utils/MusicUtils.h"
#include "Utils/SceneUtils.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace ui;

Scene* Settings::createScene()
{
	auto scene = Scene::create();
	auto layer = Settings::create();
	scene->addChild(layer);
	return scene;
}

/*游戏设置场景初始化 ×*/
bool Settings::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*背景*/
	SceneUtils::setBGimage("BGimage/Background.png", this, SceneUtils::setBGimageWith::TextureCache);

	/*菜单所有按钮统一处理*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "Back","Music","Effect","Music","Music","Effect","Effect" };//后续将后四个改为音量调节按钮
	//按钮回调函数
	vector<void (Settings::*)(Ref* pSender)> CallbackVector = { &Settings::settingsBackCallback,&Settings::settingsMusicCallback,
																&Settings::settingsEffectCallback,&Settings::settingsMusicDownCallback,
																&Settings::settingsMusicUpCallback,&Settings::settingsEffectDownCallback,
																&Settings::settingsEffectUpCallback };
	//按钮尺寸
	vector<float> ScaleVector = { 1, 1, 1, 1, 1 ,1 ,1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0,1),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5)
	};
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(origin.x, visibleSize.height + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 250),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150),
		Vec2(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 250),
		Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y - 250),
	};
	/*逐个设置坐标，存入Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItem* button = MenuItemImage::create(
			"button/" + stringVector.at(i) + "-Normal.png",
			"button/" + stringVector.at(i) + "-Active.png",
			bind(CallbackVector.at(i), this, std::placeholders::_1));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneUtils::problemLoading(stringVector.at(i).c_str());
		else
		{
			button->setScale(ScaleVector.at(i));
			button->setAnchorPoint(AnchorVector.at(i));
			button->setPosition(PositionVector.at(i));
		}
		MenuItemVector.pushBack(button);
	}

	/*总的菜单，包含以上菜单选项*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	/*创建音乐音量文本*/
	Text* musicVolume = Text::create("10", "fonts/Marker Felt.ttf", 24);
	if (musicVolume == nullptr)
	{
		SceneUtils::problemLoading("musicVolumeText creating failed");
	}
	else
	{
		musicVolume->setPosition(Vec2(visibleSize.width / 2 + origin.x + 125, visibleSize.height / 2 + origin.y - 150));
		_musicVolumeText = musicVolume;
		this->addChild(musicVolume);
	}


	/*创建音效音量文本*/
	Text* effectVolume = Text::create("10", "fonts/Marker Felt.ttf", 24);
	if (effectVolume == nullptr)
	{
		SceneUtils::problemLoading("effectVolumeText creating failed");
	}
	else
	{
		effectVolume->setPosition(Vec2(visibleSize.width / 2 + origin.x + 125, visibleSize.height / 2 + origin.y - 250));
		_effectVolumeText = effectVolume;
		this->addChild(effectVolume);
	}

	/*创建音乐开关文本*/
	Text* music = Text::create("ON", "fonts/Marker Felt.ttf", 24);
	if (music == nullptr)
	{
		SceneUtils::problemLoading("musicText creating failed");
	}
	else
	{
		music->setPosition(Vec2(visibleSize.width / 2 + origin.x + 75, visibleSize.height / 2 + origin.y + 250));
		_musicText = music;
		this->addChild(music);
	}

	/*创建音效开关文本*/
	Text* effect = Text::create("ON", "fonts/Marker Felt.ttf", 24);
	if (effect == nullptr)
	{
		SceneUtils::problemLoading("effectText creating failed");
	}
	else
	{
		effect->setPosition(Vec2(visibleSize.width / 2 + origin.x + 75, visibleSize.height / 2 + origin.y + 150));
		_effectText = effect;
		this->addChild(effect);
	}

	return true;
}

/*按键回调函数具体实现*/

/*回到菜单*/
void Settings::settingsBackCallback(Ref* pSender)
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

/*音乐开关*/
void  Settings::settingsMusicCallback(Ref* pSender)
{
	if (MusicUtils::_musicOn == true)
	{
		MusicUtils::_musicOn = false;
		_musicText->setString("OFF");//改变文本
		AudioEngine::pause(MusicUtils::_musicID);//暂停当前音乐
	}
	else if (MusicUtils::_musicOn == false)
	{
		MusicUtils::_musicOn = true;
		_musicText->setString("ON");//改变文本
		AudioEngine::resume(MusicUtils::_musicID);//继续播放当前音乐
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*音效开关*/
void  Settings::settingsEffectCallback(Ref* pSender)
{
	MusicUtils::_effectOn = !MusicUtils::_effectOn;
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	if (MusicUtils::_effectOn == true)
	{
		_effectText->setString("ON");//改变文本
	}
	else if (MusicUtils::_effectOn == false)
	{
		_effectText->setString("OFF");//改变文本
	}
}
/*音乐增强*/
void  Settings::settingsMusicUpCallback(Ref* pSender)
{
	if (MusicUtils::_musicVolume < 10)
	{
		++MusicUtils::_musicVolume;
		_musicVolumeText->setString(StringUtils::toString(MusicUtils::_musicVolume));//改变文本
		AudioEngine::setVolume(MusicUtils::_musicID, MusicUtils::_musicVolume / 10.0f);//即时设置当前播放音乐的音量
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*音乐减弱*/
void  Settings::settingsMusicDownCallback(Ref* pSender)
{
	if (MusicUtils::_musicVolume > 0)
	{
		--MusicUtils::_musicVolume;
		_musicVolumeText->setString(StringUtils::toString(MusicUtils::_musicVolume));//改变文本
		AudioEngine::setVolume(MusicUtils::_musicID, MusicUtils::_musicVolume / 10.0f);//即时设置当前播放音乐的音量
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*音效增强*/
void  Settings::settingsEffectUpCallback(Ref* pSender)
{
	if (MusicUtils::_effectVolume < 10)
	{
		++MusicUtils::_effectVolume;
		_effectVolumeText->setString(StringUtils::toString(MusicUtils::_effectVolume));//改变文本
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*音效减弱*/
void  Settings::settingsEffectDownCallback(Ref* pSender)
{
	if (MusicUtils::_effectVolume > 0)
	{
		--MusicUtils::_effectVolume;
		_effectVolumeText->setString(StringUtils::toString(MusicUtils::_effectVolume));//改变文本
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
