#ifndef __OPENINGANIMATION_H_
#define __OPENINGANIMATION_H_

#include "cocos2d.h"

USING_NS_CC;

class OpeningAnimation : public Scene
{
public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene();
	virtual bool init();

	void EnterMenu(float dt);

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(OpeningAnimation);
};

#endif // !__OPENINGANIMATION_H_