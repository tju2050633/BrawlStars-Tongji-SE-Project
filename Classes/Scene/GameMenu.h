#ifndef __MENU_H_
#define __MENU_H_

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

/*���ж�ָʾ���˵�����
�ⲿ����Ҫʵ��init�������Ǽ����ص�����ֻ���л��������ѣ���������̫��
init����Ҳд�Ĳ���ˣ���ʣ�ز�·��������yֵ����ϸ�ڣ��������ı������
������Ƶ����Ҫ����һλͬѧ����һ�£�SimpleAudioEngine�ƺ���cocos������Ƶ��һ����
*/

USING_NS_CC;

class GameMenu : public Layer
{
private:
	/*��initʹ�õĳ�ʼ������*/
	void initMenu(); //��ʼ���˵�
	void initTrophy(); //��ʼ��������ǩ

	/*�����ص�����*/
	void menuSinglePlayerCallback(Ref *pSender); //����ģʽ
	void menuMultiPlayerCallback(Ref *pSender);	 //����ģʽ
	void menuSettingsCallback(Ref *pSender);	 //��Ϸ����
	void menuInstructionCallback(Ref *pSender);	 //��Ϸ˵��
	void menuQuitCallback(Ref *pSender);		 //�˳���Ϸ

public:
	/*���������ͳ�ʼ��*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameMenu);
};

#endif // !__MENU_H_