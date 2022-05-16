#ifndef __MENU_H_
#define __MENU_H_

#include "cocos2d.h"

/*���ж�ָʾ���˵�����
�ⲿ����Ҫʵ��init�������Ǽ����ص�����ֻ���л��������ѣ���������̫��
init����Ҳд�Ĳ���ˣ���ʣ�ز�·��������yֵ����ϸ�ڣ��������ı������
������Ƶ����Ҫ����һλͬѧ����һ�£�SimpleAudioEngine�ƺ���cocos������Ƶ��һ����

���⣬����problemLoading()�������ÿ��cpp��дһ��о����ã�Ӧ�ÿ���дһ��Ȼ��external��չ�����ļ�ɶ�ģ�
���֪ʶ���ˣ����ǵõľ͸����Ż�һ��
*/

class GameMenu : public cocos2d::Scene
{
public:
	/*���������ͳ�ʼ��*/
	static cocos2d::Scene* createScene();
	virtual bool init();

	/*�����ص�����*/
	void menuSinglePlayerCallback(cocos2d::Ref* pSender);   //����ģʽ
	void menuMultiPlayerCallback(cocos2d::Ref* pSender);    //����ģʽ
	void menuSettingsCallback(cocos2d::Ref* pSender);       //��Ϸ����
	void menuInstructionCallback(cocos2d::Ref* pSender);    //��Ϸ˵��
	void menuQuitCallback(cocos2d::Ref* pSender);           //�˳���Ϸ

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(GameMenu);
};

#endif //__MENU_H_