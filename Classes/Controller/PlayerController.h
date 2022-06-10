#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"
#include "Controller/ControllerListener.h"

USING_NS_CC;

class PlayerController :public Node {
	/*监听对象*/
	CC_SYNTHESIZE(ControllerListener*, _controllerListener, ControllerListener);

	/*键盘监听器*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);

	/*鼠标监听器*/
	CC_SYNTHESIZE(EventListenerMouse*, _mouseListener, MouseListener);

	/*控制器图标*/
	CC_SYNTHESIZE(Sprite*, _controllerSprite, ControllerSprite);
	CC_SYNTHESIZE(Sprite*, _attackCenterSprite, AttackCenterSprite);
	CC_SYNTHESIZE(Sprite*, _abilityCenterSprite, AbilityCenterSprite);
	CC_SYNTHESIZE(Sprite*, _abilityRoundSprite, AbilityRoundSprite);
	/*按钮图标*/
	CC_SYNTHESIZE(Rect, _rectReturnButton, RectReturnButton);
	CC_SYNTHESIZE(Rect, _rectEmotionButton, RectEmotionButton);
	/*攻击和技能图标的原位置*/
	CC_SYNTHESIZE(Vec2, _attackCenterOriginPosition, AttackCenterOriginPosition);
	CC_SYNTHESIZE(Vec2, _abilityCenterOriginPosition, AbilityCenterOriginPosition);

	/*监听WASD键按下状态*/
	bool _keyW;
	bool _keyA;
	bool _keyS;
	bool _keyD;

public:
	CREATE_FUNC(PlayerController);

	virtual bool init();

	/*键盘监听器*/
	void initKeyboardListener();

	/*键盘监听器回调函数*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	/*鼠标监听器*/
	void initMouseListener();

	/*鼠标监听器回调函数*/
	void onMouseDown(Event* event);
	void onMouseUp(Event* event);
	void onMouseMove(Event* event);

	/*计算鼠标相对玩家的角度*/
	float calculateAngle(Vec2 cursorPosition, Vec2 playerPosition);

	/*改变控制器图标*/
	void changeControllerSprite();
	/*攻击、技能按钮偏移*/
	void buttonMove(Sprite* sprite, Vec2 originPosition, float angle);
};

#endif // !__CONTROLLER_H_
