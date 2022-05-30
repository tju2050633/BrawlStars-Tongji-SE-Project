#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;

class PlayerController :public Node {
	/*��������*/
	CC_SYNTHESIZE(ControllerListener*, _controllerListener, ControllerListener);
	/*����ͼ��*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);
	/*���̼�����*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);
	/*��������*/
	CC_SYNTHESIZE(EventListenerMouse*, _mouseListener, MouseListener);

public:
	CREATE_FUNC(PlayerController);

	virtual bool init();

	/*���̼�����*/
	void KeyboardListener();
	/*��������*/
	void MouseListener();
};

#endif // !__CONTROLLER_H_
