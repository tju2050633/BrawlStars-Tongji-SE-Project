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

/*��Ϸ���ó�����ʼ�� ��*/
bool Settings::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*����*/
	SceneUtils::setBGimage("BGimage/Background.png", this, SceneUtils::setBGimageWith::TextureCache);

	/*�˵����а�ťͳһ����*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "Back","Music","Effect","Music","Music","Effect","Effect" };//���������ĸ���Ϊ�������ڰ�ť
	//��ť�ص�����
	vector<void (Settings::*)(Ref* pSender)> CallbackVector = { &Settings::settingsBackCallback,&Settings::settingsMusicCallback,
																&Settings::settingsEffectCallback,&Settings::settingsMusicDownCallback,
																&Settings::settingsMusicUpCallback,&Settings::settingsEffectDownCallback,
																&Settings::settingsEffectUpCallback };
	//��ť�ߴ�
	vector<float> ScaleVector = { 1, 1, 1, 1, 1 ,1 ,1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(0,1),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5)
	};
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(origin.x, visibleSize.height + origin.y),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 250),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150),
		Vec2(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 250),
		Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y - 250),
	};
	/*����������꣬����Vector*/
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

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	/*�������������ı�*/
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


	/*������Ч�����ı�*/
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

	/*�������ֿ����ı�*/
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

	/*������Ч�����ı�*/
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

/*�����ص���������ʵ��*/

/*�ص��˵�*/
void Settings::settingsBackCallback(Ref* pSender)
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

/*���ֿ���*/
void  Settings::settingsMusicCallback(Ref* pSender)
{
	if (MusicUtils::_musicOn == true)
	{
		MusicUtils::_musicOn = false;
		_musicText->setString("OFF");//�ı��ı�
		AudioEngine::pause(MusicUtils::_musicID);//��ͣ��ǰ����
	}
	else if (MusicUtils::_musicOn == false)
	{
		MusicUtils::_musicOn = true;
		_musicText->setString("ON");//�ı��ı�
		AudioEngine::resume(MusicUtils::_musicID);//�������ŵ�ǰ����
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*��Ч����*/
void  Settings::settingsEffectCallback(Ref* pSender)
{
	MusicUtils::_effectOn = !MusicUtils::_effectOn;
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	if (MusicUtils::_effectOn == true)
	{
		_effectText->setString("ON");//�ı��ı�
	}
	else if (MusicUtils::_effectOn == false)
	{
		_effectText->setString("OFF");//�ı��ı�
	}
}
/*������ǿ*/
void  Settings::settingsMusicUpCallback(Ref* pSender)
{
	if (MusicUtils::_musicVolume < 10)
	{
		++MusicUtils::_musicVolume;
		_musicVolumeText->setString(StringUtils::toString(MusicUtils::_musicVolume));//�ı��ı�
		AudioEngine::setVolume(MusicUtils::_musicID, MusicUtils::_musicVolume / 10.0f);//��ʱ���õ�ǰ�������ֵ�����
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*���ּ���*/
void  Settings::settingsMusicDownCallback(Ref* pSender)
{
	if (MusicUtils::_musicVolume > 0)
	{
		--MusicUtils::_musicVolume;
		_musicVolumeText->setString(StringUtils::toString(MusicUtils::_musicVolume));//�ı��ı�
		AudioEngine::setVolume(MusicUtils::_musicID, MusicUtils::_musicVolume / 10.0f);//��ʱ���õ�ǰ�������ֵ�����
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*��Ч��ǿ*/
void  Settings::settingsEffectUpCallback(Ref* pSender)
{
	if (MusicUtils::_effectVolume < 10)
	{
		++MusicUtils::_effectVolume;
		_effectVolumeText->setString(StringUtils::toString(MusicUtils::_effectVolume));//�ı��ı�
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
/*��Ч����*/
void  Settings::settingsEffectDownCallback(Ref* pSender)
{
	if (MusicUtils::_effectVolume > 0)
	{
		--MusicUtils::_effectVolume;
		_effectVolumeText->setString(StringUtils::toString(MusicUtils::_effectVolume));//�ı��ı�
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}
