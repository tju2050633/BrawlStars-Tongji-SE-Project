#ifndef __OPENING_ANIMATION_H_
#define __OPENING_ANIMATION_H_

#include "cocos2d.h"

USING_NS_CC;

class OpeningAnimation : public Layer
{
public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OpeningAnimation);

	/*预加载所有图片、音频等资源*/
	void PreloadResource();

	/*切换到游戏菜单*/
	void EnterMenu(float dt);

	void plistImageAsyncCallback(Texture2D* texture);
};

#endif // !__OPENING_ANIMATION_H_