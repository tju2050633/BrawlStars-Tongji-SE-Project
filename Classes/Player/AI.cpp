#include <cmath>
#include "Player/AI.h"
#include "Entity/Brawler.h"
#include "Scene/GameScene.h"
#include "Controller/PlayerController.h"

bool AI::init()
{
	_nearestBox = nullptr;
	_nearestBrawler = nullptr;
	_nearestBuff = nullptr;
	_destination = Vec2::ZERO;
	_target = nullptr;

	_X_Direction_Modity = true;
	_Y_Direction_Modity = true;

	_animationAvailable = true;
	_isAvoidingWall = false;

	this->scheduleUpdate();
	this->schedule(SEL_SCHEDULE(&AI::update1s), 1.0f);
	this->schedule(SEL_SCHEDULE(&AI::update05s), 0.5f);

	return true;
}

//设置位置
void AI::update(float dt)
{
	//更新移速
	if(!_brawler->getIsCastingAbility())
		updateMoveSpeed();

	//更新位置
	Vec2 aiPos = getPosition() + Vec2(_brawler->getMoveSpeedX() * dt, _brawler->getMoveSpeedY() * dt);

	//若位置为墙体，改变速度
	if (GameScene::getGameScene()->isWallTile(aiPos))
	{
		//X方向尝试避开
		if (getBrawler()->getMoveSpeedX() == 0)
		{
			//更新速度修正
			if (getBrawler()->getMoveSpeedY() > 0)
				_Y_Direction_Modity = false;
			else
				_Y_Direction_Modity = true;

			//根据之前的速度修正调整速度
			getBrawler()->setMoveSpeedY(0);
			if (_X_Direction_Modity)
				getBrawler()->setMoveSpeedX(getBrawler()->getMoveSpeed());
			else
				getBrawler()->setMoveSpeedX(-getBrawler()->getMoveSpeed());
		}
		//Y方向尝试避开
		else if (getBrawler()->getMoveSpeedY() == 0)
		{
			//更新速度修正
			if (getBrawler()->getMoveSpeedX() > 0)
				_X_Direction_Modity = false;
			else
				_X_Direction_Modity = true;

			//根据之前的速度修正调整速度
			getBrawler()->setMoveSpeedX(0);
			if (_Y_Direction_Modity)
				getBrawler()->setMoveSpeedY(getBrawler()->getMoveSpeed());
			else
				getBrawler()->setMoveSpeedY(-getBrawler()->getMoveSpeed());
		}

		//更新目标位置
		aiPos = getPosition() + Vec2(_brawler->getMoveSpeedX() * dt, _brawler->getMoveSpeedY() * dt);

		//设置正在避开墙体
		_isAvoidingWall = true;

		scheduleOnce([&](float dt) {
			_isAvoidingWall = false;
			}, 0.5f, "avoidingWall");
	}

	//设置位置
	GameScene::getGameScene()->setTargetPosition(this, aiPos);

	//更新草丛视野
	updateBushVisibility();
}

void AI::updateMoveSpeed()
{
	//避开墙体机制起作用时，不因目标改变速度
	if (_isAvoidingWall)
		return;

	//更新移速
	float moveSpeedAngle;
	if (fabs(_destination.x - getPosition().x) < 1e-6 && _destination.y >= getPosition().y)
		moveSpeedAngle = M_PI / 2;
	else if (fabs(_destination.x - getPosition().x) < 1e-6 && _destination.y < getPosition().y)
		moveSpeedAngle = -M_PI / 2;
	else
		moveSpeedAngle = atan((_destination.y - getPosition().y) / (_destination.x - getPosition().x));

	/*角度修正*/
	if (_destination.x < getPosition().x)
		moveSpeedAngle += M_PI;

	//根据目的地角度在四个pi/2分布，设置x、y速度，同一时间只有一个方向有速度
	AnimationUtils::EntityEnum brawler = _brawler->getAnimateBrawler();
	float time = 0.6;
	float interval = 0.1;
	INT32 iFrameNum = brawler == AnimationUtils::Stu ? 1 : 3;
	INT32 loop = -1;

	if (moveSpeedAngle >= -M_PI_4 && moveSpeedAngle <= M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(_brawler, brawler, AnimationUtils::Right, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_brawler->setMoveSpeedX(_brawler->getMoveSpeed());
		_brawler->setMoveSpeedY(0);
	}
	else if (moveSpeedAngle >= M_PI_4 && moveSpeedAngle <= 3 * M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(_brawler, brawler, AnimationUtils::Top, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_brawler->setMoveSpeedX(0);
		_brawler->setMoveSpeedY(_brawler->getMoveSpeed());
	}
	else if (moveSpeedAngle >= 3 * M_PI_4 && moveSpeedAngle <= 5 * M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(_brawler, brawler, AnimationUtils::Left, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_brawler->setMoveSpeedX(-_brawler->getMoveSpeed());
		_brawler->setMoveSpeedY(0);
	}
	else if (moveSpeedAngle >= 5 * M_PI_4 || moveSpeedAngle <= -M_PI_4)
	{
		if (_animationAvailable)
		{
			AnimationUtils::runAnimate(_brawler, brawler, AnimationUtils::Bottom, time, iFrameNum, loop);
			_animationAvailable = false;
			scheduleOnce([&](float dt) {
				_animationAvailable = true;
				}, interval, "animationInterval");
		}
		_brawler->setMoveSpeedX(0);
		_brawler->setMoveSpeedY(-_brawler->getMoveSpeed());
	}
}

void AI::updateBushVisibility()
{
	//可以看见附近英雄
	if (_nearestBrawler && _nearestBrawler->getInBush() && _nearestBrawler->getParent()->getPosition().distance(getPosition()) < 100)
	{
		_nearestBrawler->getParent()->setVisible(true);
		_nearestBrawler->getSprite()->setOpacity(100);
		_nearestBrawler->setInBush(false);
	}

	//在草丛里且附近没有英雄，设置属性、对玩家不可见
	Point tileCoord = GameScene::getGameScene()->tileCoordForPosition(getPosition());
	auto grass = GameScene::getGameScene()->getGrass();
	if (!grass->getTileAt(tileCoord))	//不在草里，不透明
	{
		this->setVisible(true);
		this->getBrawler()->getSprite()->setOpacity(255);
		this->getBrawler()->setInBush(false);
	}
	else if (_nearestBrawler && _nearestBrawler->getParent()->getPosition().distance(getPosition()) > 100)//在草里，且周围无英雄，隐身、在草里
	{
		this->setVisible(false);
		this->getBrawler()->setInBush(true);
	}
	else if (_nearestBrawler && _nearestBrawler->getParent()->getPosition().distance(getPosition()) < 100)   //在草里但周围有人，半透明、属性为可见
	{
		this->setVisible(true);
		this->getBrawler()->getSprite()->setOpacity(100);
		this->getBrawler()->setInBush(false);
	}
}

//做出行为
void AI::update05s(float dt)
{
	if (!_target)
	{
		return;
	}

	Vec2 pos = getPosition();
	//目标物在攻击范围内
	if (pos.distance(_targetPos) < _attackRange)
	{
		//直接攻击、放技能
		_brawler->attack(_angle);

		_brawler->castAbility(_angle);
	}
}

//更新信息
void AI::update1s(float dt)
{
	//更新最近的信息，再做出决策
	updateNearestBrawler();
	updateNearestBox();
	updateNearestBuff();

	//更新目的地
	float vision = 500;	//视距
	Vec2 pos = getPosition();
	Vec2 otherPos = _nearestBrawler->getParent()->getPosition();
	if (vision < otherPos.getDistance(getPosition()) || _nearestBrawler->getInBush())
	{
		//不在视距内，直接无视英雄，前往buff/宝箱
		if (_nearestBuff)
		{
			_destination = _nearestBuff->getPosition();
			_target = nullptr;
			_targetPos = Vec2(-1000, -1000);
		}
		else if (_nearestBox)
		{
			_destination = _nearestBox->getPosition();
			_target = _nearestBox;
			_targetPos = _target->getPosition();
		}
	}
	else
	{
		//在视距内，直接开杀
		_destination = otherPos;
		_target = _nearestBrawler;
		_targetPos = _nearestBrawler->getParent()->getPosition();
	}

	//更新目标角度
	if (fabs(_targetPos.x - pos.x) < 1e-6 && _targetPos.y >= pos.y)
		_angle = M_PI / 2;
	else if (fabs(_targetPos.x - pos.x) < 1e-6 && _targetPos.y < pos.y)
		_angle = -M_PI / 2;
	else
		_angle = atan((_targetPos.y - pos.y) / (_targetPos.x - pos.x));

	/*角度修正*/
	if (_targetPos.x < pos.x)
		_angle += M_PI;
}

//获取最近的英雄
void AI::updateNearestBrawler()
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	//获取距离最近的英雄
	Vector<Brawler*> brawlerVec = GameScene::getGameScene()->getBrawlerVector();
	for (int i = 0; i < brawlerVec.size(); i++)
	{
		//除去自己
		if (brawlerVec.at(i) == _brawler)
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
		_nearestBrawler = brawlerVec.at(index);
	else
		_nearestBrawler = nullptr;
}

//获取最近的宝箱
void AI::updateNearestBox()
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	//获取距离最近的宝箱
	Vector<Entity*> boxVec = GameScene::getGameScene()->getEntityVector();
	for (int i = 0; i < boxVec.size(); i++)
	{
		Vec2 otherPos = boxVec.at(i)->getPosition();
		float distance = otherPos.getDistance(pos);

		if (distance < minDistance)
		{
			minDistance = distance;
			index = i;
		}
	}
	if (!boxVec.empty())
		_nearestBox = boxVec.at(index);
	else
		_nearestBox = nullptr;
}

//获取最近的buff
void AI::updateNearestBuff()
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	//获取距离最近的buff
	Vector<Sprite*> buffVec = GameScene::getGameScene()->getBuffVector();
	for (int i = 0; i < buffVec.size(); i++)
	{
		Vec2 otherPos = buffVec.at(i)->getPosition();
		float distance = otherPos.getDistance(pos);

		if (distance < minDistance)
		{
			minDistance = distance;
			index = i;
		}
	}
	if (!buffVec.empty())
		_nearestBuff = buffVec.at(index);
	else
		_nearestBuff = nullptr;
}