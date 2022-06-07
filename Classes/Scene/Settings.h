#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "cocos2d.h"
#include "ui/UIText.h"

USING_NS_CC;
using namespace ui;

class Settings : public Layer
{
private:
	/*UI*/
	Text* _musicText;//音乐开关文本
	Text* _effectText;//音效开关文本
	Text* _musicVolumeText;//音乐音量大小文本
	Text* _effectVolumeText;//音效音量大小文本


	/*按键回调函数*/
	void settingsBackCallback(Ref* pSender);     //回到菜单
	void settingsMusicCallback(Ref* pSender);	 //音乐开关
	void settingsEffectCallback(Ref* pSender);	 //音效开关
	void settingsMusicUpCallback(Ref* pSender);	 //音乐增强
	void settingsMusicDownCallback(Ref* pSender);	 //音乐减弱
	void settingsEffectUpCallback(Ref* pSender);	 //音效增强
	void settingsEffectDownCallback(Ref* pSender);	 //音效减弱


public:
	/*创建场景和初始化*/
	virtual bool init();
	static Scene* createScene();
	/*自动生成create()的宏*/
	CREATE_FUNC(Settings);
};

#endif // !__SETTINGS_H_