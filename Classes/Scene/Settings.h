#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "cocos2d.h"

USING_NS_CC;

class Settings : public Layer
{
private:
	/*���� �ص�����*/
	void menuBackCallback(Ref* pSender);

public:
	/*���������ͳ�ʼ��*/
	virtual bool init();

	static Scene* createScene();

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(Settings);
};

#endif // !__SETTINGS_H_