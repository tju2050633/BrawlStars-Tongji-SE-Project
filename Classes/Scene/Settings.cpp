#include "cocos2d.h"
#include "Settings.h"
#include "GameMenu.h"

USING_NS_CC;

/*��ó������� ��*/
Scene* Settings::createScene()
{
	return Settings::create();
}

/*��Ϸ���ó�����ʼ�� ��*/
bool Settings::init()
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

	return true;
}