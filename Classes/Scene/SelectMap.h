#ifndef __SELECT_MAP_H_
#define __SELECT_MAP_H_

#include "cocos2d.h"

USING_NS_CC;

class SelectMap : public Layer
{
private:
	/*��initʹ�õĳ�ʼ������*/
	void initMenu();	//��ʼ���˵�

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
	CREATE_FUNC(SelectMap);
};

#endif // !__SELECT_MAP_H_