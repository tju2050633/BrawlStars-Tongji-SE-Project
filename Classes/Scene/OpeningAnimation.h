#ifndef __OPENINGANIMATION_H_
#define __OPENINGANIMATION_H_

#include "cocos2d.h"

USING_NS_CC;

class OpeningAnimation : public Scene
{
public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();

	void EnterMenu(float dt);

	/*自动生成create()的宏*/
	CREATE_FUNC(OpeningAnimation);
};

#endif // !__OPENINGANIMATION_H_