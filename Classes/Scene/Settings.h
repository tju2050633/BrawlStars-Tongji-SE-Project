#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "cocos2d.h"

class Settings : public cocos2d::Scene
{
public:
	/*���������ͳ�ʼ��*/
	static cocos2d::Scene* createScene();
	virtual bool init();

	/*�����ص�����*/

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(Settings);
};

#endif // __SETTINGS_H_