#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "cocos2d.h"

USING_NS_CC;

class Settings : public Layer
{
private:
	/*返回 回调函数*/
	void menuBackCallback(Ref* pSender);

public:
	/*创建场景和初始化*/
	virtual bool init();

	static Scene* createScene();

	/*自动生成create()的宏*/
	CREATE_FUNC(Settings);
};

#endif // !__SETTINGS_H_