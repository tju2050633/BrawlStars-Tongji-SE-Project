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
	Text* _musicText;//���ֿ����ı�
	Text* _effectText;//��Ч�����ı�
	Text* _musicVolumeText;//����������С�ı�
	Text* _effectVolumeText;//��Ч������С�ı�


	/*�����ص�����*/
	void settingsBackCallback(Ref* pSender);     //�ص��˵�
	void settingsMusicCallback(Ref* pSender);	 //���ֿ���
	void settingsEffectCallback(Ref* pSender);	 //��Ч����
	void settingsMusicUpCallback(Ref* pSender);	 //������ǿ
	void settingsMusicDownCallback(Ref* pSender);	 //���ּ���
	void settingsEffectUpCallback(Ref* pSender);	 //��Ч��ǿ
	void settingsEffectDownCallback(Ref* pSender);	 //��Ч����


public:
	/*���������ͳ�ʼ��*/
	virtual bool init();
	static Scene* createScene();
	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(Settings);
};

#endif // !__SETTINGS_H_