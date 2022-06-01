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

	_keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}

/*���̼������ص�����*/
void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
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
	/*���Ŷ���*/
	if (_keyD)
	{
		Vector<SpriteFrame*> frames;
		auto spriteFrameCache = SpriteFrameCache::getInstance();
		spriteFrameCache->addSpriteFramesWithFile("Animation/PrimoRight.plist");
		for (int i = 1; i <= 9; i++)
		{
			auto frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format("Primo_%d.png", i).c_str());
			frames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(frames, 1.5f / 9.0f, -1);

		auto animate = Animate::create(animation);

		_controllerListener->getTargetBrawler()->setRunningAnimate(animate);
		_controllerListener->getTargetBrawler()->getSprite()->setScale(1);
		_controllerListener->getTargetBrawler()->getSprite()->runAction(animate);
	}
}

void PlayerController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*�ɿ����̼�����WASD������Ӧ��д������ֱ����ö�Ӧ�ٶ�Ϊ0*/
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		if (!_keyS)	//�ж϶�Ӧ�ļ�δ���£����ø÷����ٶ�Ϊ0����ֹ����S��ͬʱ����W���ɿ�SʱW�����˵��ٶ�Ϊ0.
			_controllerListener->setTargetMoveSpeedY(0);
		_keyW = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (!_keyD)
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

	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D)
	{
		auto animate = _controllerListener->getTargetBrawler()->getRunningAnimate();
		_controllerListener->getTargetBrawler()->getSprite()->stopAction(animate);
		_controllerListener->getTargetBrawler()->setRunningAnimate(nullptr);
		_controllerListener->getTargetBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Primo_1.png"));
	}
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
	Sprite* rangeIndicator = _controllerListener->getTargetBrawler()->getRangeIndicator();
	auto mouseKey = e->getMouseButton();

	/*����������ĽǶ�*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*����������Ҽ�����*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		/*������ťͼ���ƶ�*/
		_attackCenterSprite->setOpacity(255);
		buttonMove(_attackCenterSprite, _attackCenterOriginPosition, angle);
		/*��Χָʾ����ʾ����ת*/
		rangeIndicator->setVisible(true);
		rangeIndicator->setRotation(-angle * 180 / M_PI + 15);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		/*���ܰ�ťͼ���ƶ�*/
		_abilityRoundSprite->setVisible(true);
		_abilityCenterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AbilityCenter.png"));
		_abilityCenterSprite->setPosition(_abilityCenterSprite->getPosition() + Vec2(45, 85));
		buttonMove(_abilityCenterSprite, _abilityCenterOriginPosition + Vec2(45, 85), angle);
		/*��Χָʾ����ʾ����ת*/
		rangeIndicator->setVisible(true);
		rangeIndicator->setScale(1.25);
		rangeIndicator->setColor(Color3B::YELLOW);
		rangeIndicator->setRotation(-angle * 180 / M_PI + 15);
	}
}

void PlayerController::onMouseUp(Event* event)
{
	/*��ȡ�¼���������ꡢ������ꡢ��갴��*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//������꣬�Ǵ�������ϵ�µ�����
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//��Ҵ�������ϵ������=��Ե�ͼ����+��ͼƫ����
	Sprite* rangeIndicator = _controllerListener->getTargetBrawler()->getRangeIndicator();
	auto mouseKey = e->getMouseButton();

	/*����������ĽǶ�*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*����������Ҽ�����*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		_controllerListener->getTargetBrawler()->attack(angle);
		/*������ťͼ��ָ�*/
		_attackCenterSprite->setOpacity(150);
		_attackCenterSprite->setPosition(_attackCenterOriginPosition);
		/*��Χָʾ������ʾ*/
		rangeIndicator->setVisible(false);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		_controllerListener->getTargetBrawler()->castAbility(angle);
		/*���ܰ�ťͼ��ָ�*/
		_abilityRoundSprite->setVisible(false);
		_abilityCenterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Ability.png"));
		_abilityCenterSprite->setPosition(_abilityCenterOriginPosition);
		/*��Χָʾ������ʾ���ָ�ԭ����*/
		rangeIndicator->setScale(0.8);
		rangeIndicator->setColor(Color3B::WHITE);
		rangeIndicator->setVisible(false);
	}
}

void PlayerController::onMouseMove(Event* event)
{
	/*��ȡ�¼���������ꡢ������ꡢ��갴��*/
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());								//������꣬�Ǵ�������ϵ�µ�����
	Vec2 playerPosition = _controllerListener->getTargetPosition() + getParent()->getPosition();//��Ҵ�������ϵ������=��Ե�ͼ����+��ͼƫ����
	Sprite* rangeIndicator = _controllerListener->getTargetBrawler()->getRangeIndicator();
	auto mouseKey = e->getMouseButton();

	/*����������ĽǶ�*/
	float angle = calculateAngle(cursorPosition, playerPosition);

	/*����������Ҽ�����*/
	if (mouseKey == EventMouse::MouseButton::BUTTON_LEFT)
	{
		/*������ťͼ���ƶ�*/
		buttonMove(_attackCenterSprite, _attackCenterOriginPosition, angle);
		/*��Χָʾ����ת*/
		rangeIndicator->setRotation(-angle * 180 / M_PI + 15);
	}
	else if (mouseKey == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		/*���ܰ�ťͼ���ƶ�*/
		buttonMove(_abilityCenterSprite, _abilityCenterOriginPosition + Vec2(45, 85), angle);
		/*��Χָʾ����ת*/
		rangeIndicator->setRotation(-angle * 180 / M_PI + 15);
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