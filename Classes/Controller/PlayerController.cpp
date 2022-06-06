#include <cmath>
#include "Controller/PlayerController.h"
#include "Entity/Brawler.h"
#include "Utils/AnimationUtils.h"
#include "Scene/GameScene.h"

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

	_keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}

/*键盘监听器回调函数*/
void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*动画参数*/
	AnimationUtils::EntityEnum brawler = _controllerListener->getTargetBrawler()->getAnimateBrawler();
	float time = 0.6;
	INT32 iFrameNum = brawler == AnimationUtils::Stu? 1 : 3;
	INT32 loop = -1;

	/*按下键盘监听，WASD（及对应大写情况）分别设置对象速度，运行动画，并替换控制器图标*/
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W)
	{
		_controllerListener->setTargetMoveSpeedY(_controllerListener->getTargetBrawler()->getMoveSpeed());
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Top, time, iFrameNum, loop);
		_keyW = true;
		_keyS = false;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A)
	{
		_controllerListener->setTargetMoveSpeedX(-_controllerListener->getTargetBrawler()->getMoveSpeed());
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Left, time, iFrameNum, loop);
		_keyA = true;
		_keyD = false;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S)
	{
		_controllerListener->setTargetMoveSpeedY(-_controllerListener->getTargetBrawler()->getMoveSpeed());
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Bottom, time, iFrameNum, loop);
		_keyS = true;
		_keyW = false;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D)
	{
		_controllerListener->setTargetMoveSpeedX(_controllerListener->getTargetBrawler()->getMoveSpeed());
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Right, time, iFrameNum, loop);
		_keyD = true;
		_keyA = false;
	}

	changeControllerSprite();
}

void PlayerController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	AnimationUtils::TypeEnum currentDirection = AnimationUtils::Bottom;
	/*松开键盘监听，WASD（及对应大写情况）分别设置对应速度为0*/
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W)
	{
		if (!_keyS)//判断对应的键未按下，才置该方向速度为0。防止按下S的同时按下W，松开S时W按下了但速度为0.
			_controllerListener->setTargetMoveSpeedY(0);
		_keyW = false;
		currentDirection = AnimationUtils::Top;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A)
	{
		if (!_keyD)
			_controllerListener->setTargetMoveSpeedX(0);
		_keyA = false;
		currentDirection = AnimationUtils::Left;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S)
	{
		if (!_keyW)
			_controllerListener->setTargetMoveSpeedY(0);
		_keyS = false;
		currentDirection = AnimationUtils::Bottom;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D)
	{
		if (!_keyA)
			_controllerListener->setTargetMoveSpeedX(0);
		_keyD = false;
		currentDirection = AnimationUtils::Right;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Q || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Q)
		_controllerListener->getTargetBrawler()->takeDamage(100);
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_E || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_E)
		_controllerListener->getTargetBrawler()->dealDamage(1000);
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_R || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_R)
		_controllerListener->getTargetBrawler()->setAnimateBrawler(AnimationUtils::bear);
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Z || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Z)
		_controllerListener->getTargetBrawler()->takeBuff();
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_X || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_X)
		_controllerListener->getTargetBrawler()->kill(_controllerListener->getTargetBrawler());

	changeControllerSprite();

	/*动画参数*/
	AnimationUtils::EntityEnum brawler = _controllerListener->getTargetBrawler()->getAnimateBrawler();
	float time = 0.6;
	INT32 iFrameNum = brawler == AnimationUtils::Stu ? 1 : 3;
	INT32 loop = -1;

	/*松开按键后还剩一个按键激活，动画设为该方向；无按键激活，设为松开键的方向*/
	if (_keyW)
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Top, time, iFrameNum, loop);
	else if (_keyA)
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Left, time, iFrameNum, loop);
	else if (_keyS)
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Bottom, time, iFrameNum, loop);
	else if (_keyD)
		AnimationUtils::runAnimate(_controllerListener->getTargetBrawler(), brawler, AnimationUtils::Right, time, iFrameNum, loop);
	else
		AnimationUtils::stopAnimate(_controllerListener->getTargetBrawler(), brawler, currentDirection);
}

/*鼠标监听器*/
void PlayerController::initMouseListener() {
	_mouseListener = EventListenerMouse::create();

	_mouseListener->onMouseDown = CC_CALLBACK_1(PlayerController::onMouseDown, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(PlayerController::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(PlayerController::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

/*鼠标监听器回调函数*/
void PlayerController::onMouseDown(Event* event)
{
	/*获取事件、鼠标坐标、玩家坐标、范围指示器、鼠标按键*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//鼠标坐标，是窗口坐标系下的坐标
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//玩家窗口坐标系下坐标=相对地图坐标+地图偏移量
	auto mouseKey = e->getMouseButton();

	/*点按钮时无反应*/
	if (_rectReturnButton.containsPoint(cursorPosition) || _rectEmotionButton.containsPoint(cursorPosition))
		return;

	/*获得鼠标坐标的角度*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*左键攻击，右键技能*/
	Sprite* rangeIndicator;
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		rangeIndicator = _controllerListener->getTargetBrawler()->getRangeIndicatorAttack();
		/*攻击按钮图标移动*/
		_attackCenterSprite->setOpacity(255);
		buttonMove(_attackCenterSprite, _attackCenterOriginPosition, angle);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		rangeIndicator = _controllerListener->getTargetBrawler()->getRangeIndicatorAbility();
		if (_controllerListener->getTargetBrawler()->getEnergy() == _controllerListener->getTargetBrawler()->getMaxEnergy())
		{
			/*能量已满可以释放技能时，技能按钮图标移动*/
			buttonMove(_abilityCenterSprite, _abilityCenterOriginPosition + Vec2(45, 85), angle);
		}
	}
	/*范围指示器显示、旋转*/
	rangeIndicator->setVisible(true);
	rangeIndicator->setRotation(-angle * 180 / M_PI);
}

void PlayerController::onMouseUp(Event* event)
{
	/*获取事件、鼠标坐标、玩家坐标、鼠标按键*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//鼠标坐标，是窗口坐标系下的坐标
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//玩家窗口坐标系下坐标=相对地图坐标+地图偏移量
	auto mouseKey = e->getMouseButton();

	/*获得鼠标坐标的角度*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*左键攻击，右键技能*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		/*攻击按钮图标恢复*/
		_attackCenterSprite->setOpacity(150);
		_attackCenterSprite->setPosition(_attackCenterOriginPosition);
		/*范围指示器不显示*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAttack()->setVisible(false);

		/*点按钮时无反应*/
		if (_rectReturnButton.containsPoint(cursorPosition) || _rectEmotionButton.containsPoint(cursorPosition))
			return;

		_controllerListener->getTargetBrawler()->attack(angle);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		/*技能按钮图标恢复*/
		_abilityRoundSprite->setVisible(false);
		_abilityCenterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Ability.png"));
		_abilityCenterSprite->setPosition(_abilityCenterOriginPosition);
		/*范围指示器不显示*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAbility()->setVisible(false);

		/*点按钮时无反应*/
		if (_rectReturnButton.containsPoint(cursorPosition) || _rectEmotionButton.containsPoint(cursorPosition))
			return;

		_controllerListener->getTargetBrawler()->castAbility(angle);
	}
}

void PlayerController::onMouseMove(Event* event)
{
	/*获取事件、鼠标坐标、玩家坐标、鼠标按键*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//鼠标坐标，是窗口坐标系下的坐标
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//玩家窗口坐标系下坐标=相对地图坐标+地图偏移量
	auto mouseKey = e->getMouseButton();

	/*获得鼠标坐标的角度*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*左键攻击，右键技能*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		/*攻击按钮图标移动*/
		buttonMove(_attackCenterSprite, _attackCenterOriginPosition, angle);
		/*范围指示器旋转*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAttack()->setRotation(-angle * 180 / M_PI);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		if (_controllerListener->getTargetBrawler()->getEnergy() == _controllerListener->getTargetBrawler()->getMaxEnergy())
		{
			/*能量已满时，技能按钮图标移动*/
			buttonMove(_abilityCenterSprite, _abilityCenterOriginPosition + Vec2(45, 85), angle);
		}
		/*范围指示器旋转*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAbility()->setRotation(-angle * 180 / M_PI);
	}
}

/*计算鼠标相对玩家的角度*/
float PlayerController::calculateAngle(Vec2 cursorPosition, Vec2 playerPosition)
{
	float angle;
	if (fabs(cursorPosition.x - playerPosition.x) < 1e-6 && cursorPosition.y >= playerPosition.y)
		angle = M_PI / 2;
	else if (fabs(cursorPosition.x - playerPosition.x) < 1e-6 && cursorPosition.y < playerPosition.y)
		angle = -M_PI / 2;
	else
		angle = atan((cursorPosition.y - playerPosition.y) / (cursorPosition.x - playerPosition.x));

	/*角度修正*/
	if (cursorPosition.x < playerPosition.x)
		angle += M_PI;

	return angle;
}

/*控制器精灵图标变化*/
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

/*攻击、技能按钮偏移*/
void PlayerController::buttonMove(Sprite* sprite, Vec2 originPosition, float angle)
{
	INT32 radius = 80;
	Vec2 newPosition = originPosition + Vec2(radius * cos(angle), radius * sin(angle));
	sprite->setPosition(newPosition);
}