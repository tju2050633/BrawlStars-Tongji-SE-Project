#include <cmath>
#include "Controller/PlayerController.h"
#include "Entity/Brawler.h"

bool PlayerController::init()
{
	initKeyboardListener();
	initMouseListener();
	_keyW = false;
	_keyA = false;
	_keyS = false;
	_keyD = false;
	return true;
}

/*���̼�����*/
void PlayerController::initKeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();

	_keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		/*���¼��̼�����WASD������Ӧ��д������ֱ����ö����ٶȣ����滻������ͼ��*/
		switch (keyCode)
		{
			case cocos2d::EventKeyboard::KeyCode::KEY_W:
				_controllerListener->setTargetMoveSpeedY(_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyW = true;	//���ö�Ӧ����״̬Ϊ���£�Ϊ��֤ͬһʱ��������������������ʱ��Ӧ�ļ�Ϊδ����
				_keyS = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_A:
				_controllerListener->setTargetMoveSpeedX(-_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyA = true;
				_keyD = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_S:
				_controllerListener->setTargetMoveSpeedY(-_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyS = true;
				_keyW = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_D:
				_controllerListener->setTargetMoveSpeedX(_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyD = true;
				_keyA = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
				_controllerListener->setTargetMoveSpeedY(_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyW = true;
				_keyS = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
				_controllerListener->setTargetMoveSpeedX(-_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyA = true;
				_keyD = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
				_controllerListener->setTargetMoveSpeedY(-_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyS = true;
				_keyW = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
				_controllerListener->setTargetMoveSpeedX(_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyD = true;
				_keyA = false;
				break;
			default:
				break;
		}
		changeControllerSprite();
	};

	_keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		/*�ɿ����̼�����WASD������Ӧ��д������ֱ����ö�Ӧ�ٶ�Ϊ0*/
		switch (keyCode)
		{
			case cocos2d::EventKeyboard::KeyCode::KEY_W:
				if(!_keyS)	//�ж϶�Ӧ�ļ�δ���£����ø÷����ٶ�Ϊ0����ֹ����S��ͬʱ����W���ɿ�SʱW�����˵��ٶ�Ϊ0.
					_controllerListener->setTargetMoveSpeedY(0);
				_keyW = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_A:
				if(!_keyD)
					_controllerListener->setTargetMoveSpeedX(0);
				_keyA = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_S:
				if (!_keyW)
					_controllerListener->setTargetMoveSpeedY(0);
				_keyS = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_D:
				if (!_keyA)
					_controllerListener->setTargetMoveSpeedX(0);
				_keyD = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
				if (!_keyS)
					_controllerListener->setTargetMoveSpeedY(0);
				_keyW = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
				if (!_keyD)
					_controllerListener->setTargetMoveSpeedX(0);
				_keyA = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
				if (!_keyW)
					_controllerListener->setTargetMoveSpeedY(0);
				_keyS = false;
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
				if (!_keyA)
					_controllerListener->setTargetMoveSpeedX(0);
				_keyD = false;
				break;
			default:
				break;
		}
		changeControllerSprite();
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}
/*��������*/
void PlayerController::initMouseListener() {
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

void PlayerController::changeControllerSprite()
{
	SpriteFrame* frame;

	//Top
	if(_keyW && !_keyA && !_keyS && !_keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-Top.png");
	//Left
	else if (!_keyW && _keyA && !_keyS && !_keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-Left.png");
	//Bottom
	else if (!_keyW && !_keyA && _keyS && !_keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-Bottom.png");
	//Right
	else if (!_keyW && !_keyA && !_keyS && _keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-Right.png");
	//LeftTop
	else if (_keyW && _keyA && !_keyS && !_keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-LeftTop.png");
	//LeftBottom
	else if (!_keyW && _keyA && _keyS && !_keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-LeftBottom.png");
	//RightTop
	else if (_keyW && !_keyA && !_keyS && _keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-RightTop.png");
	//RightBottom
	else if (!_keyW && !_keyA && _keyS && _keyD)
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Active-RightBottom.png");
	//Normal
	else
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Controller-Normal.png");

	_controllerSprite->setSpriteFrame(frame);
}