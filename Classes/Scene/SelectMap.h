#ifndef __SELECTMAP_H_
#define __SELECTMAP_H_

#include "cocos2d.h"

/*���ж�ָʾ��ѡ���ͼ����
��Menu�������ƣ������Ѿ����
��Ҫ���Ƶ�ϸ�ڣ�
init������Դ·����xy����ֵ�������ص�������create()���������ͺ�ֵ������һ����������Ϣ��
*/

USING_NS_CC;

class SelectMap : public Scene
{
private:
	/*��initʹ�õĳ�ʼ������*/
	void initMenu();	//��ʼ���˵�
	void initBG();		//��ʼ������

	/*ѡ���ͼ �ص�����*/
	void menuMapACallback(Ref* pSender);   //��ͼA
	void menuMapBCallback(Ref* pSender);   //��ͼB
	void menuMapCCallback(Ref* pSender);   //��ͼC

	/*���� �ص�����*/
	void menuBackCallback(Ref* pSender);

public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene();
	virtual bool init();

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(SelectMap);
};

#endif // !__SELECTMAP_H_