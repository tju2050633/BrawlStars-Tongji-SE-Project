#include "cocos2d.h"
#include "OpeningAnimation.h"
#include "GameMenu.h"

USING_NS_CC;

/*��ó������� ��*/
Scene* OpeningAnimation::createScene()
{
	return OpeningAnimation::create();
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

	return true;
}