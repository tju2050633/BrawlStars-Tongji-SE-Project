#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;

class PlayerController :public Node {
	/*��������*/
	CC_SYNTHESIZE(ControllerListener*, _controllerListener, ControllerListener);

	/*���̼�����*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);

	/*��������*/
	CC_SYNTHESIZE(EventListenerMouse*, _mouseListener, MouseListener);

	/*������ͼ��*/
	CC_SYNTHESIZE(Sprite*, _controllerSprite, ControllerSprite);

	/*����WASD������״̬*/
	bool _keyW;
	bool _keyA;
	bool _keyS;
	bool _keyD;

public:
	CREATE_FUNC(PlayerController);

	virtual bool init();

	/*���̼�����*/
	void initKeyboardListener();
	/*��������*/
	void initMouseListener();

	/*�ı������ͼ��*/
	void changeControllerSprite();
};

#endif // !__CONTROLLER_H_
