#ifndef __OPENING_ANIMATION_H_
#define __OPENING_ANIMATION_H_

#include "cocos2d.h"

USING_NS_CC;

class OpeningAnimation : public Layer
{
public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OpeningAnimation);

	/*Ԥ��������ͼƬ����Ƶ����Դ*/
	void PreloadResource();

	/*�л�����Ϸ�˵�*/
	void EnterMenu(float dt);

	void plistImageAsyncCallback(Texture2D* texture);
};

#endif // !__OPENING_ANIMATION_H_