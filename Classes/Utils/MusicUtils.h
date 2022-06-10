#pragma once
#ifndef _MUSIC_UTILS_H_
#define _MUSIC_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;

class MusicUtils {
public:
	/*
		ALL BGM：
		"Music/Menu.mp3" in  OpeningAnimation  GameMenu Instruction Settings SelectMap SelectBrawler Room
		"Music/Final.mp3" in GameScene
		"Music/Combat.mp3" in GameScene
		"Music/Victory.mp3" in GameScene
		"Music/Defeat.mp3" in GameScene
	*/
	/*静态成员变量，存储各音效选项*/
	static bool _musicOn;			//记录是否播放音乐
	static bool _effectOn;			//记录是否播放音效
	static INT32 _musicVolume;		//记录音乐音量
	static INT32 _effectVolume;		//记录音效音量
	static INT32 _musicID;          //当前播放的音乐ID

	/*共用，播放特定音量的背景音乐*/
	static void playMusic(const std::string& filePath);
	/*共用，播放特定音量的声效*/
	static void playEffect(const std::string& filePath);
	
};

#endif