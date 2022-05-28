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

	/*���̼����ص�����*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	/*�������ص�����*/
	void onMouseDown(Event* event);
	void onMouseUp(Event* event);

public:
	CREATE_FUNC(PlayerController);
	virtual bool init();

	/*��ʼ�����̼�����*/
	void initKeyboardListener();
	/*��ʼ����������*/
	void initMouseListener();
};

#endif // !__CONTROLLER_H_
