#include <cmath>
#include "Controller/PlayerController.h"
#include "Entity/Brawler.h"

bool PlayerController::init()
{
	KeyboardListener();
	MouseListener();
	return true;
}

/*���̼�����*/
void PlayerController::KeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();

	_keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
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
		return true;
	};

	_keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
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
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}
void PlayerController::MouseListener() {
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = [&](Event* event) {
		/*������ʾ���������ܷ���*/
	};
	_mouseListener->onMouseUp = [&](Event* event) {
		/*��ȡ�¼���������ꡢ������ꡢ��갴��*/
		EventMouse* e = (EventMouse*)event;
		Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());
		Vec2 playerPosition = _controllerListener->getTargetPosition();
		auto mouseKey = e->getMouseButton();

		/*���������Ϊԭ�㣬�����������ĽǶ�*/
		float angle;
		if (fabs(cursorPosition.x - playerPosition.x < 1e-6) && cursorPosition.y >= playerPosition.y)
			angle = M_PI / 2;
		else if (fabs(cursorPosition.x - playerPosition.x < 1e-6) && cursorPosition.y < playerPosition.y)
			angle = -M_PI / 2;
		else
			angle = atan((cursorPosition.y - playerPosition.y) / (cursorPosition.x - playerPosition.x));

		/*����������Ҽ�����*/
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
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}