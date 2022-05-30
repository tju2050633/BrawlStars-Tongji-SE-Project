#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;

class PlayerController :public Node {
	/*¼àÌı¶ÔÏó*/
	CC_SYNTHESIZE(ControllerListener*, _controllerListener, ControllerListener);
	/*¾«ÁéÍ¼±ê*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);
	/*¼üÅÌ¼àÌıÆ÷*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);
	/*Êó±ê¼àÌıÆ÷*/
	CC_SYNTHESIZE(EventListenerMouse*, _mouseListener, MouseListener);

public:
	CREATE_FUNC(PlayerController);

	virtual bool init();

	/*¼üÅÌ¼àÌıÆ÷*/
	void KeyboardListener();
	/*Êó±ê¼àÌıÆ÷*/
	void MouseListener();
};

#endif // !__CONTROLLER_H_
