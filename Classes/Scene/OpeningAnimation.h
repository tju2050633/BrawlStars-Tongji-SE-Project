#ifndef __OPENINGANIMATION_H_
#define __OPENINGANIMATION_H_

#include "cocos2d.h"

class OpeningAnimation : public cocos2d::Scene
{
public:
	/*���������ͳ�ʼ��*/
	static cocos2d::Scene* createScene();
	virtual bool init();

	/*�����ص�����*/

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(OpeningAnimation);
};


#endif // __OPENINGANIMATION_H_