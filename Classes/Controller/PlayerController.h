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
	CC_SYNTHESIZE(Sprite*, _attackCenterSprite, AttackCenterSprite);
	CC_SYNTHESIZE(Sprite*, _abilityCenterSprite, AbilityCenterSprite);
	CC_SYNTHESIZE(Sprite*, _abilityRoundSprite, AbilityRoundSprite);
	/*��ťͼ��*/
	CC_SYNTHESIZE(Rect, _rectReturnButton, RectReturnButton);
	CC_SYNTHESIZE(Rect, _rectEmotionButton, RectEmotionButton);
	/*�����ͼ���ͼ���ԭλ��*/
	CC_SYNTHESIZE(Vec2, _attackCenterOriginPosition, AttackCenterOriginPosition);
	CC_SYNTHESIZE(Vec2, _abilityCenterOriginPosition, AbilityCenterOriginPosition);

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

	/*���̼������ص�����*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	/*��������*/
	void initMouseListener();

	/*���������ص�����*/
	void onMouseDown(Event* event);
	void onMouseUp(Event* event);
	void onMouseMove(Event* event);

	/*������������ҵĽǶ�*/
	float calculateAngle(Vec2 cursorPosition, Vec2 playerPosition);

	/*�ı������ͼ��*/
	void changeControllerSprite();
	/*���������ܰ�ťƫ��*/
	void buttonMove(Sprite* sprite, Vec2 originPosition, float angle);
};

#endif // !__CONTROLLER_H_
