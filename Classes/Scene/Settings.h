#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "cocos2d.h"

USING_NS_CC;

class Settings : public Scene
{
public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene();
	virtual bool init();

	/*�����ص�����*/

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(Settings);
};

#endif // !__SETTINGS_H_