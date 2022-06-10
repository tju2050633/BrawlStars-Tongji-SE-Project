#include "Entity/Bear.h"
#include "Constant/Const.h"
#include "Scene/GameScene.h"

bool Bear::init()
{
	//属性初始化
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

	//添加进GameScene的数组
	GameScene::getGameScene()->pushBackEntity(this);

	this->scheduleUpdate();
	this->schedule(SEL_SCHEDULE(&Bear::update1s), 1.0f);
	this->schedule(SEL_SCHEDULE(&Bear::update05s), 0.5f);

	return true;
}

void Bear::update(float dt)
{
	//更新移速
	updateMoveSpeed();

	//更新位置
	Vec2 pos = getPosition() + Vec2(_moveSpeedX * dt, _moveSpeedY * dt);

	//若位置为墙体，改变速度
	if (GameScene::getGameScene()->isWallTile(pos))
	{
		//X方向尝试避开
		if (_moveSpeedX == 0)
		{
			//更新速度修正
			if (_moveSpeedY > 0)
				_Y_Direction_Modity = false;
			else
				_Y_Direction_Modity = true;

			//根据之前的速度修正调整速度
			_moveSpeedY = 0;
			if (_X_Direction_Modity)
				_moveSpeedX = _moveSpeed;
			else
				_moveSpeedX = -_moveSpeed;
		}
		//Y方向尝试避开
		else if (_moveSpeedY == 0)
		{
			//更新速度修正
			if (_moveSpeedX > 0)
				_X_Direction_Modity = false;
			else
				_X_Direction_Modity = true;

			//根据之前的速度修正调整速度
			_moveSpeedX = 0;
			if (_Y_Direction_Modity)
				_moveSpeedY = _moveSpeed;
			else
				_moveSpeedY = -_moveSpeed;
		}

		//更新目标位置
		pos = getPosition() + Vec2(_moveSpeedX * dt, _moveSpeedY * dt);

		//设置正在避开墙体
		_isAvoidingWall = true;

		scheduleOnce([&](float dt) {
			_isAvoidingWall = false;
			}, 0.5f, "avoidingWall");
	}

	//设置位置
	GameScene::getGameScene()->setTargetPosition(this, pos);
}

void Bear::updateMoveSpeed()
{
	//避开墙体机制起作用时，不因目标改变速度
	if (_isAvoidingWall)
		return;

	//更新移速
	float moveSpeedAngle;
	if (fabs(_targetPos.x - getPosition().x) < 1e-6 && _targetPos.y >= getPosition().y)
		moveSpeedAngle = M_PI / 2;
	else if (fabs(_targetPos.x - getPosition().x) < 1e-6 && _targetPos.y < getPosition().y)
		moveSpeedAngle = -M_PI / 2;
	else
		moveSpeedAngle = atan((_targetPos.y - getPosition().y) / (_targetPos.x - getPosition().x));

	/*角度修正*/
	if (_targetPos.x < getPosition().x)
		moveSpeedAngle += M_PI;

	//根据目的地角度在四个pi/2分布，设置x、y速度，同一时间只有一个方向有速度
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

//做出行为
void Bear::update05s(float dt)
{
	if (!_target)
	{
		return;
	}

	Vec2 pos = getPosition();
	//目标物在攻击范围内直接攻击
	if (pos.distance(_targetPos) < _attackRange)
	{
		attack(_target);
	}
}

//获取距离最近的英雄
void Bear::update1s(float dt)
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	Vector<Brawler*> brawlerVec = GameScene::getGameScene()->getBrawlerVector();
	for (int i = 0; i < brawlerVec.size(); i++)
	{
		//除去主人和在草丛里的
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