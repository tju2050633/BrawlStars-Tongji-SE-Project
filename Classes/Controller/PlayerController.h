#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;


class PlayerController :public Node {
	/*监听对象*/
	CC_SYNTHESIZE(ControllerListener*, _controllerListener, ControllerListener);
	/*精灵图标*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);
	/*键盘监听器*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);
	/*鼠标监听器*/
	CC_SYNTHESIZE(EventListenerMouse*, _mouseListener, MouseListener);

	/*键盘监听回调函数*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	/*鼠标监听回调函数*/
	void onMouseDown(Event* event);
	void onMouseUp(Event* event);

public:
	CREATE_FUNC(PlayerController);
	virtual bool init();

	/*初始化键盘监听器*/
	void initKeyboardListener();
	/*初始化鼠标监听器*/
	void initMouseListener();
};

#endif // !__CONTROLLER_H_
