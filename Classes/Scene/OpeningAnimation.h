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

	/*加载欢迎图标*/
	void LoadWelcomeLabel();

	/*预加载所有图片、音频等资源*/
	void PreloadResource();

	/*切换到游戏菜单*/
	void EnterMenu(float dt);

	/*自动生成create()的宏*/
	CREATE_FUNC(OpeningAnimation);
};

#endif // !__OPENINGANIMATION_H_