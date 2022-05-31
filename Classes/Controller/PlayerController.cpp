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

/*键盘监听器*/
void PlayerController::initKeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();

	_keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		/*按下键盘监听，WASD（及对应大写情况）分别设置对象速度，并替换控制器图标*/
		switch (keyCode)
		{
			case cocos2d::EventKeyboard::KeyCode::KEY_W:
				_controllerListener->setTargetMoveSpeedY(_controllerListener->getTargetBrawler()->getMoveSpeed());
				_keyW = true;	//设置对应键的状态为按下，为保证同一时刻最多两个键视作激活，此时对应的键为未按下
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
		/*松开键盘监听，WASD（及对应大写情况）分别设置对应速度为0*/
		switch (keyCode)
		{
			case cocos2d::EventKeyboard::KeyCode::KEY_W:
				if(!_keyS)	//判断对应的键未按下，才置该方向速度为0。防止按下S的同时按下W，松开S时W按下了但速度为0.
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
/*鼠标监听器*/
void PlayerController::initMouseListener() {
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = [&](Event* event) {
		/*这里显示攻击、技能方向*/
	};
	_mouseListener->onMouseUp = [&](Event* event) {
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