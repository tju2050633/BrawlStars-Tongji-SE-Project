#include "cocos2d.h"
#include "Instruction.h"
#include "GameMenu.h"

USING_NS_CC;

/*��Ϸ˵�� ������ʼ�� ��*/
bool Instruction::init()
{
	/*��ʼ������*/
	if (!Layer::init())
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