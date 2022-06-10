#include "MusicUtils.h"
#include<String>
#include "audio/include/AudioEngine.h"


USING_NS_CC;

bool MusicUtils::_musicOn = true;			//��¼�Ƿ񲥷�����
bool MusicUtils::_effectOn = true;			//��¼�Ƿ񲥷���Ч
INT32 MusicUtils::_musicVolume = 10;		//��¼��������
INT32 MusicUtils::_effectVolume = 10;		//��¼��Ч����
INT32 MusicUtils::_musicID = 0;							//��ǰ���ŵ�����ID

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