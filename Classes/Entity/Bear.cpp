#include "Entity/Bear.h"
#include "Constant/Const.h"
#include "Scene/GameScene.h"

bool Bear::init()
{
	//���Գ�ʼ��
	_currentHealthPoint = _healthPoint = BEAR_HP;
	_attackDamage = BEAR_AD;
	_moveSpeed = BEAR_MS;
	_moveSpeedX = 0;
	_moveSpeedY = 0;
	_attackInterval = BEAR_AI;
	_attackRange = BEAR_ATTACK_RANGE;

	_target = nullptr;
	_targetPos = Vec2::ZERO;

	_X_Direction_Modity = true;
	_Y_Direction_Modity = true;

	_animationAvailable = true;
	_isAvoidingWall = false;

	//��ӽ�GameScene������
	GameScene::getGameScene()->pushBackEntity(this);

	this->scheduleUpdate();
	this->schedule(SEL_SCHEDULE(&Bear::update1s), 1.0f);
	this->schedule(SEL_SCHEDULE(&Bear::update05s), 0.5f);

	return true;
}

void Bear::update(float dt)
{
	//��������
	updateMoveSpeed();

	//����λ��
	Vec2 pos = getPosition() + Vec2(_moveSpeedX * dt, _moveSpeedY * dt);

	//��λ��Ϊǽ�壬�ı��ٶ�
	if (GameScene::getGameScene()->isWallTile(pos))
	{
		//X�����Աܿ�
		if (_moveSpeedX == 0)
		{
			//�����ٶ�����
			if (_moveSpeedY > 0)
				_Y_Direction_Modity = false;
			else
				_Y_Direction_Modity = true;

			//����֮ǰ���ٶ����������ٶ�
			_moveSpeedY = 0;
			if (_X_Direction_Modity)
				_moveSpeedX = _moveSpeed;
			else
				_moveSpeedX = -_moveSpeed;
		}
		//Y�����Աܿ�
		else if (_moveSpeedY == 0)
		{
			//�����ٶ�����
			if (_moveSpeedX > 0)
				_X_Direction_Modity = false;
			else
				_X_Direction_Modity = true;

			//����֮ǰ���ٶ����������ٶ�
			_moveSpeedX = 0;
			if (_Y_Direction_Modity)
				_moveSpeedY = _moveSpeed;
			else
				_moveSpeedY = -_moveSpeed;
		}

		//����Ŀ��λ��
		pos = getPosition() + Vec2(_moveSpeedX * dt, _moveSpeedY * dt);

		//�������ڱܿ�ǽ��
		_isAvoidingWall = true;

		scheduleOnce([&](float dt) {
			_isAvoidingWall = false;
			}, 0.5f, "avoidingWall");
	}

	//����λ��
	GameScene::getGameScene()->setTargetPosition(this, pos);
}

void Bear::updateMoveSpeed()
{
	//�ܿ�ǽ�����������ʱ������Ŀ��ı��ٶ�
	if (_isAvoidingWall)
		return;

	//��������
	float moveSpeedAngle;
	if (fabs(_targetPos.x - getPosition().x) < 1e-6 && _targetPos.y >= getPosition().y)
		moveSpeedAngle = M_PI / 2;
	else if (fabs(_targetPos.x - getPosition().x) < 1e-6 && _targetPos.y < getPosition().y)
		moveSpeedAngle = -M_PI / 2;
	else
		moveSpeedAngle = atan((_targetPos.y - getPosition().y) / (_targetPos.x - getPosition().x));

	/*�Ƕ�����*/
	if (_targetPos.x < getPosition().x)
		moveSpeedAngle += M_PI;

	//����Ŀ�ĵؽǶ����ĸ�pi/2�ֲ�������x��y�ٶȣ�ͬһʱ��ֻ��һ���������ٶ�
	AnimationUtils::EntityEnum brawler = AnimationUtils::bear;
	float time = 0.6;
	float interval = 0.1;
	INT32 iFrameNum = brawler == AnimationUtils::Stu ? 1 : 3;
	INT32 loop = -1;

	if (moveSpeedAngle >= -M_PI_4 && moveSpeedAngle <= M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(this, brawler, AnimationUtils::Right, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_moveSpeedX = _moveSpeed;
		_moveSpeedY = 0;
	}
	else if (moveSpeedAngle >= M_PI_4 && moveSpeedAngle <= 3 * M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(this, brawler, AnimationUtils::Top, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_moveSpeedX = 0;
		_moveSpeedY = _moveSpeed;
	}
	else if (moveSpeedAngle >= 3 * M_PI_4 && moveSpeedAngle <= 5 * M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(this, brawler, AnimationUtils::Left, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_moveSpeedX = -_moveSpeed;
		_moveSpeedY = 0;
	}
	else if (moveSpeedAngle >= 5 * M_PI_4 || moveSpeedAngle <= -M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(this, brawler, AnimationUtils::Bottom, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_moveSpeedX = 0;
		_moveSpeedY = -_moveSpeed;
	}
}

//������Ϊ
void Bear::update05s(float dt)
{
	if (!_target)
	{
		return;
	}

	Vec2 pos = getPosition();
	//Ŀ�����ڹ�����Χ��ֱ�ӹ���
	if (pos.distance(_targetPos) < _attackRange)
	{
		attack(_target);
	}
}

//��ȡ���������Ӣ��
void Bear::update1s(float dt)
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	Vector<Brawler*> brawlerVec = GameScene::getGameScene()->getBrawlerVector();
	for (int i = 0; i < brawlerVec.size(); i++)
	{
		//��ȥ���˺��ڲݴ����
		if (brawlerVec.at(i) == _owner || brawlerVec.at(i)->getInBush())
			continue;

		Vec2 otherPos = brawlerVec.at(i)->getParent()->getPosition();
		float distance = otherPos.getDistance(pos);

		if (distance < minDistance)
		{
			minDistance = distance;
			index = i;
		}
	}
	if (!brawlerVec.empty())
	{
		_target = brawlerVec.at(index);
		_targetPos = _target->getParent()->getPosition();
	}
	else
		_target = nullptr;

}

void Bear::attack(Brawler* brawler)
{
	if (getPosition().distance(brawler->getParent()->getPosition()) > _attackRange)
		return;

	AnimationUtils::runAnimate(this, AnimationUtils::bear, AnimationUtils::Attack, 0.6, 2, 1);
	if (brawler->takeDamage(_attackDamage))
		_target = nullptr;
}

void Bear::die()
{
	_owner->setBear(nullptr);
	Entity::die();
}