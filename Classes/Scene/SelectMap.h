#ifndef __SELECTMAP_H_
#define __SELECTMAP_H_

#include "cocos2d.h"

/*���ж�ָʾ��ѡ���ͼ����
��Menu�������ƣ������Ѿ����
��Ҫ���Ƶ�ϸ�ڣ�
init������Դ·����xy����ֵ�������ص�������create()���������ͺ�ֵ������һ����������Ϣ��
*/

class SelectMap : public cocos2d::Scene
{
public:
	/*���������ͳ�ʼ��*/

	static cocos2d::Scene* createScene();
	virtual bool init();

	/*ѡ���ͼ �ص�����*/
	void menuMapACallback(cocos2d::Ref* pSender);   //��ͼA
	void menuMapBCallback(cocos2d::Ref* pSender);   //��ͼB
	void menuMapCCallback(cocos2d::Ref* pSender);   //��ͼC

	/*���� �ص�����*/
	void menuBackCallback(cocos2d::Ref* pSender);

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(SelectMap);
};

#endif //__SELECTMAP_H_