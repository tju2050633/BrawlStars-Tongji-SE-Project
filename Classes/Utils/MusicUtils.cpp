#include "MusicUtils.h"
#include<String>
#include "audio/include/AudioEngine.h"


USING_NS_CC;

bool MusicUtils::_musicOn = true;			//记录是否播放音乐
bool MusicUtils::_effectOn = true;			//记录是否播放音效
INT32 MusicUtils::_musicVolume = 10;		//记录音乐音量
INT32 MusicUtils::_effectVolume = 10;		//记录音效音量
INT32 MusicUtils::_musicID = 0;							//当前播放的音乐ID

void MusicUtils::playMusic(const std::string &filePath ) 
{
	if (_musicOn)
	{
		AudioEngine::stopAll();
		_musicID = AudioEngine::play2d(filePath, true, _musicVolume / 10.0f);
	}
}

void MusicUtils::playEffect(const std::string& filePath) 
{
	if (_effectOn);
		AudioEngine::play2d(filePath, false, _effectVolume / 10.0f);
}