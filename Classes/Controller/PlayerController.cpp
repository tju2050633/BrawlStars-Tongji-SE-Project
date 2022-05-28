#include "Controller/PlayerController.h"
#include "Entity/Brawler.h"

bool PlayerController::init()
{
	initKeyboardListener();
	initMouseListener();

	return true;
}

/*��ʼ�����̼�����*/
void PlayerController::initKeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}

/*��ʼ����������*/
void PlayerController::initMouseListener()
{
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(PlayerController::onMouseDown, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(PlayerController::onMouseUp, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

/*���̼����ص�����*/
void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*���¼��̼�����WASD������Ӧ��д������ֱ����ö����ٶ�*/
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		_controllerListener->setTargetMoveSpeedY(_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		_controllerListener->setTargetMoveSpeedX(-_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		_controllerListener->setTargetMoveSpeedY(-_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		_controllerListener->setTargetMoveSpeedX(_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
		_controllerListener->setTargetMoveSpeedY(_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
		_controllerListener->setTargetMoveSpeedX(-_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
		_controllerListener->setTargetMoveSpeedY(-_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
		_controllerListener->setTargetMoveSpeedX(_controllerListener->getTargetBrawler()->getMoveSpeed());
		break;
	default:
		break;
	}
}

void PlayerController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*�ɿ����̼�����WASD������Ӧ��д������ֱ����ö�Ӧ�ٶ�Ϊ0*/
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		_controllerListener->setTargetMoveSpeedY(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		_controllerListener->setTargetMoveSpeedX(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		_controllerListener->setTargetMoveSpeedY(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		_controllerListener->setTargetMoveSpeedX(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
		_controllerListener->setTargetMoveSpeedY(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
		_controllerListener->setTargetMoveSpeedX(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
		_controllerListener->setTargetMoveSpeedY(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
		_controllerListener->setTargetMoveSpeedX(0);
		break;
	default:
		break;
	}
}

/*�������ص�����*/
void PlayerController::onMouseDown(Event* event)
{
	/*������ʾ���������ܷ���*/
}

void PlayerController::onMouseUp(Event* event)
{
	/*����������Ҽ�����*/
	EventMouse* e = (EventMouse*)event;

	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());

	auto mouseKey = e->getMouseButton();
	if(mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
		_controllerListener->setTargetPosition(cursorPosition);
	else if(mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
		_controllerListener->setTargetPosition(cursorPosition + Vec2(100, 100));
}
