#pragma once
#ifndef _MUSIC_UTILS_H_
#define _MUSIC_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;

class MusicUtils {
public:
	/*
		ALL BGM��
		"Music/Menu.mp3" in  OpeningAnimation  GameMenu Instruction Settings SelectMap SelectBrawler Room
		"Music/Final.mp3" in GameScene
		"Music/Combat.mp3" in GameScene
		"Music/Victory.mp3" in GameScene
		"Music/Defeat.mp3" in GameScene
	*/
	/*��̬��Ա�������洢����Чѡ��*/
	static bool _musicOn;			//��¼�Ƿ񲥷�����
	static bool _effectOn;			//��¼�Ƿ񲥷���Ч
	static INT32 _musicVolume;		//��¼��������
	static INT32 _effectVolume;		//��¼��Ч����
	static INT32 _musicID;          //��ǰ���ŵ�����ID

	/*���ã������ض������ı�������*/
	static void playMusic(const std::string& filePath);
	/*���ã������ض���������Ч*/
	static void playEffect(const std::string& filePath);
	
};

#endif