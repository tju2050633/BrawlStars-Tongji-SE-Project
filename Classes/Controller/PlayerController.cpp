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

/*���̼�����*/
void PlayerController::initKeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();

	_keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}

/*���̼������ص�����*/
void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*��������*/
	AnimationUtils::EntityEnum brawler = _controllerListener->getTargetBrawler()->getAnimateBrawler();
	float time = 0.6;
	INT32 iFrameNum = brawler == AnimationUtils::Stu? 1 : 3;
	INT32 loop = -1;

	/*���¼��̼�����WASD������Ӧ��д������ֱ����ö����ٶȣ����ж��������滻������ͼ��*/
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
	/*�ɿ����̼�����WASD������Ӧ��д������ֱ����ö�Ӧ�ٶ�Ϊ0*/
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W)
	{
		if (!_keyS)//�ж϶�Ӧ�ļ�δ���£����ø÷����ٶ�Ϊ0����ֹ����S��ͬʱ����W���ɿ�SʱW�����˵��ٶ�Ϊ0.
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

	/*��������*/
	AnimationUtils::EntityEnum brawler = _controllerListener->getTargetBrawler()->getAnimateBrawler();
	float time = 0.6;
	INT32 iFrameNum = brawler == AnimationUtils::Stu ? 1 : 3;
	INT32 loop = -1;

	/*�ɿ�������ʣһ���������������Ϊ�÷����ް��������Ϊ�ɿ����ķ���*/
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

/*��������*/
void PlayerController::initMouseListener() {
	_mouseListener = EventListenerMouse::create();

	_mouseListener->onMouseDown = CC_CALLBACK_1(PlayerController::onMouseDown, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(PlayerController::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(PlayerController::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

/*���������ص�����*/
void PlayerController::onMouseDown(Event* event)
{
	/*��ȡ�¼���������ꡢ������ꡢ��Χָʾ������갴��*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//������꣬�Ǵ�������ϵ�µ�����
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//��Ҵ�������ϵ������=��Ե�ͼ����+��ͼƫ����
	auto mouseKey = e->getMouseButton();

	/*�㰴ťʱ�޷�Ӧ*/
	if (_rectReturnButton.containsPoint(cursorPosition) || _rectEmotionButton.containsPoint(cursorPosition))
		return;

	/*����������ĽǶ�*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*����������Ҽ�����*/
	Sprite* rangeIndicator;
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		rangeIndicator = _controllerListener->getTargetBrawler()->getRangeIndicatorAttack();
		/*������ťͼ���ƶ�*/
		_attackCenterSprite->setOpacity(255);
		buttonMove(_attackCenterSprite, _attackCenterOriginPosition, angle);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		rangeIndicator = _controllerListener->getTargetBrawler()->getRangeIndicatorAbility();
		if (_controllerListener->getTargetBrawler()->getEnergy() == _controllerListener->getTargetBrawler()->getMaxEnergy())
		{
			/*�������������ͷż���ʱ�����ܰ�ťͼ���ƶ�*/
			buttonMove(_abilityCenterSprite, _abilityCenterOriginPosition + Vec2(45, 85), angle);
		}
	}
	/*��Χָʾ����ʾ����ת*/
	rangeIndicator->setVisible(true);
	rangeIndicator->setRotation(-angle * 180 / M_PI);
}

void PlayerController::onMouseUp(Event* event)
{
	/*��ȡ�¼���������ꡢ������ꡢ��갴��*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//������꣬�Ǵ�������ϵ�µ�����
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//��Ҵ�������ϵ������=��Ե�ͼ����+��ͼƫ����
	auto mouseKey = e->getMouseButton();

	/*����������ĽǶ�*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*����������Ҽ�����*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		/*������ťͼ��ָ�*/
		_attackCenterSprite->setOpacity(150);
		_attackCenterSprite->setPosition(_attackCenterOriginPosition);
		/*��Χָʾ������ʾ*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAttack()->setVisible(false);

		/*�㰴ťʱ�޷�Ӧ*/
		if (_rectReturnButton.containsPoint(cursorPosition) || _rectEmotionButton.containsPoint(cursorPosition))
			return;

		_controllerListener->getTargetBrawler()->attack(angle);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		/*���ܰ�ťͼ��ָ�*/
		_abilityRoundSprite->setVisible(false);
		_abilityCenterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Ability.png"));
		_abilityCenterSprite->setPosition(_abilityCenterOriginPosition);
		/*��Χָʾ������ʾ*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAbility()->setVisible(false);

		/*�㰴ťʱ�޷�Ӧ*/
		if (_rectReturnButton.containsPoint(cursorPosition) || _rectEmotionButton.containsPoint(cursorPosition))
			return;

		_controllerListener->getTargetBrawler()->castAbility(angle);
	}
}

void PlayerController::onMouseMove(Event* event)
{
	/*��ȡ�¼���������ꡢ������ꡢ��갴��*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//������꣬�Ǵ�������ϵ�µ�����
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//��Ҵ�������ϵ������=��Ե�ͼ����+��ͼƫ����
	auto mouseKey = e->getMouseButton();

	/*����������ĽǶ�*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*����������Ҽ�����*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		/*������ťͼ���ƶ�*/
		buttonMove(_attackCenterSprite, _attackCenterOriginPosition, angle);
		/*��Χָʾ����ת*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAttack()->setRotation(-angle * 180 / M_PI);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		if (_controllerListener->getTargetBrawler()->getEnergy() == _controllerListener->getTargetBrawler()->getMaxEnergy())
		{
			/*��������ʱ�����ܰ�ťͼ���ƶ�*/
			buttonMove(_abilityCenterSprite, _abilityCenterOriginPosition + Vec2(45, 85), angle);
		}
		/*��Χָʾ����ת*/
		_controllerListener->getTargetBrawler()->getRangeIndicatorAbility()->setRotation(-angle * 180 / M_PI);
	}
}

/*������������ҵĽǶ�*/
float PlayerController::calculateAngle(Vec2 cursorPosition, Vec2 playerPosition)
{
	float angle;
	if (fabs(cursorPosition.x - playerPosition.x) < 1e-6 && cursorPosition.y >= playerPosition.y)
		angle = M_PI / 2;
	else if (fabs(cursorPosition.x - playerPosition.x) < 1e-6 && cursorPosition.y < playerPosition.y)
		angle = -M_PI / 2;
	else
		angle = atan((cursorPosition.y - playerPosition.y) / (cursorPosition.x - playerPosition.x));

	/*�Ƕ�����*/
	if (cursorPosition.x < playerPosition.x)
		angle += M_PI;

	return angle;
}

/*����������ͼ��仯*/
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

/*���������ܰ�ťƫ��*/
void PlayerController::buttonMove(Sprite* sprite, Vec2 originPosition, float angle)
{
	INT32 radius = 80;
	Vec2 newPosition = originPosition + Vec2(radius * cos(angle), radius * sin(angle));
	sprite->setPosition(newPosition);
}