#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;

class PlayerController :public Node {
	/*¼àÌı¶ÔÏó*/
	CC_SYNTHESIZE(ControllerListener*, _controllerListener, ControllerListener);

	/*¼üÅÌ¼àÌıÆ÷*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);

	/*Êó±ê¼àÌıÆ÷*/
	CC_SYNTHESIZE(EventListenerMouse*, _mouseListener, MouseListener);

	/*¿ØÖÆÆ÷Í¼±ê*/
	CC_SYNTHESIZE(Sprite*, _controllerSprite, ControllerSprite);

	/*¼àÌıWASD¼ü°´ÏÂ×´Ì¬*/
	bool _keyW;
	bool _keyA;
	bool _keyS;
	bool _keyD;

public:
	CREATE_FUNC(PlayerController);

	virtual bool init();

	/*¼üÅÌ¼àÌıÆ÷*/
	void initKeyboardListener();
	/*Êó±ê¼àÌıÆ÷*/
	void initMouseListener();

	/*¸Ä±ä¿ØÖÆÆ÷Í¼±ê*/
	void changeControllerSprite();
};

#endif // !__CONTROLLER_H_
