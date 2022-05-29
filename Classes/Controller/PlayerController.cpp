#include <cmath>
#include "Controller/PlayerController.h"
#include "Entity/Brawler.h"

bool PlayerController::init()
{
	initKeyboardListener();
	initMouseListener();

	return true;
}

/*初始化键盘监听器*/
void PlayerController::initKeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}

/*初始化鼠标监听器*/
void PlayerController::initMouseListener()
{
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(PlayerController::onMouseDown, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(PlayerController::onMouseUp, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

/*键盘监听回调函数*/
void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*按下键盘监听，WASD（及对应大写情况）分别设置对象速度*/
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
	/*松开键盘监听，WASD（及对应大写情况）分别设置对应速度为0*/
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

/*鼠标监听回调函数*/
void PlayerController::onMouseDown(Event* event)
{
	/*这里显示攻击、技能方向*/
}

void PlayerController::onMouseUp(Event* event)
{
	/*获取事件、鼠标坐标、玩家坐标、鼠标按键*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());
	Vec2 playerPosition = _controllerListener->getTargetPosition();
	auto mouseKey = e->getMouseButton();

	/*以玩家坐标为原点，计算鼠标坐标的角度*/
	float angle;
	if (fabs(cursorPosition.x - playerPosition.x < 1e-6) && cursorPosition.y >= playerPosition.y)
		angle = M_PI / 2;
	else if (fabs(cursorPosition.x - playerPosition.x < 1e-6) && cursorPosition.y < playerPosition.y)
		angle = -M_PI / 2;
	else
		angle = atan((cursorPosition.y - playerPosition.y) / (cursorPosition.x - playerPosition.x));

	/*左键攻击，右键技能*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		//_controllerListener->getTargetBrawler()->attack(angle);
		log(StringUtils::format("player position x = %f", _controllerListener->getTargetPosition().x).c_str());
		log(StringUtils::format("player position x = %f", _controllerListener->getTargetPosition().y).c_str());
		log(StringUtils::format("cursor position x = %f", cursorPosition.x).c_str());
		log(StringUtils::format("cursor position x = %f", cursorPosition.y).c_str());
		_controllerListener->setTargetPosition(_controllerListener->getTargetPosition() + Vec2(100 * cos(angle), 100 * sin(angle)));
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		_controllerListener->getTargetBrawler()->castAbility(angle);
	}
}
