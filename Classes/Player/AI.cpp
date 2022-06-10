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

//����λ��
void AI::update(float dt)
{
	//��������
	if(!_brawler->getIsCastingAbility())
		updateMoveSpeed();

	//����λ��
	Vec2 aiPos = getPosition() + Vec2(_brawler->getMoveSpeedX() * dt, _brawler->getMoveSpeedY() * dt);

	//��λ��Ϊǽ�壬�ı��ٶ�
	if (GameScene::getGameScene()->isWallTile(aiPos))
	{
		//X�����Աܿ�
		if (getBrawler()->getMoveSpeedX() == 0)
		{
			//�����ٶ�����
			if (getBrawler()->getMoveSpeedY() > 0)
				_Y_Direction_Modity = false;
			else
				_Y_Direction_Modity = true;

			//����֮ǰ���ٶ����������ٶ�
			getBrawler()->setMoveSpeedY(0);
			if (_X_Direction_Modity)
				getBrawler()->setMoveSpeedX(getBrawler()->getMoveSpeed());
			else
				getBrawler()->setMoveSpeedX(-getBrawler()->getMoveSpeed());
		}
		//Y�����Աܿ�
		else if (getBrawler()->getMoveSpeedY() == 0)
		{
			//�����ٶ�����
			if (getBrawler()->getMoveSpeedX() > 0)
				_X_Direction_Modity = false;
			else
				_X_Direction_Modity = true;

			//����֮ǰ���ٶ����������ٶ�
			getBrawler()->setMoveSpeedX(0);
			if (_Y_Direction_Modity)
				getBrawler()->setMoveSpeedY(getBrawler()->getMoveSpeed());
			else
				getBrawler()->setMoveSpeedY(-getBrawler()->getMoveSpeed());
		}

		//����Ŀ��λ��
		aiPos = getPosition() + Vec2(_brawler->getMoveSpeedX() * dt, _brawler->getMoveSpeedY() * dt);

		//�������ڱܿ�ǽ��
		_isAvoidingWall = true;

		scheduleOnce([&](float dt) {
			_isAvoidingWall = false;
			}, 0.5f, "avoidingWall");
	}

	//����λ��
	GameScene::getGameScene()->setTargetPosition(this, aiPos);

	//���²ݴ���Ұ
	updateBushVisibility();
}

void AI::updateMoveSpeed()
{
	//�ܿ�ǽ�����������ʱ������Ŀ��ı��ٶ�
	if (_isAvoidingWall)
		return;

	//��������
	float moveSpeedAngle;
	if (fabs(_destination.x - getPosition().x) < 1e-6 && _destination.y >= getPosition().y)
		moveSpeedAngle = M_PI / 2;
	else if (fabs(_destination.x - getPosition().x) < 1e-6 && _destination.y < getPosition().y)
		moveSpeedAngle = -M_PI / 2;
	else
		moveSpeedAngle = atan((_destination.y - getPosition().y) / (_destination.x - getPosition().x));

	/*�Ƕ�����*/
	if (_destination.x < getPosition().x)
		moveSpeedAngle += M_PI;

	//����Ŀ�ĵؽǶ����ĸ�pi/2�ֲ�������x��y�ٶȣ�ͬһʱ��ֻ��һ���������ٶ�
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
	//���Կ�������Ӣ��
	if (_nearestBrawler && _nearestBrawler->getInBush() && _nearestBrawler->getParent()->getPosition().distance(getPosition()) < 100)
	{
		_nearestBrawler->getParent()->setVisible(true);
		_nearestBrawler->getSprite()->setOpacity(100);
		_nearestBrawler->setInBush(false);
	}

	//�ڲݴ����Ҹ���û��Ӣ�ۣ��������ԡ�����Ҳ��ɼ�
	Point tileCoord = GameScene::getGameScene()->tileCoordForPosition(getPosition());
	auto grass = GameScene::getGameScene()->getGrass();
	if (!grass->getTileAt(tileCoord))	//���ڲ����͸��
	{
		this->setVisible(true);
		this->getBrawler()->getSprite()->setOpacity(255);
		this->getBrawler()->setInBush(false);
	}
	else if (_nearestBrawler && _nearestBrawler->getParent()->getPosition().distance(getPosition()) > 100)//�ڲ������Χ��Ӣ�ۣ������ڲ���
	{
		this->setVisible(false);
		this->getBrawler()->setInBush(true);
	}
	else if (_nearestBrawler && _nearestBrawler->getParent()->getPosition().distance(getPosition()) < 100)   //�ڲ��ﵫ��Χ���ˣ���͸��������Ϊ�ɼ�
	{
		this->setVisible(true);
		this->getBrawler()->getSprite()->setOpacity(100);
		this->getBrawler()->setInBush(false);
	}
}

//������Ϊ
void AI::update05s(float dt)
{
	if (!_target)
	{
		return;
	}

	Vec2 pos = getPosition();
	//Ŀ�����ڹ�����Χ��
	if (pos.distance(_targetPos) < _attackRange)
	{
		//ֱ�ӹ������ż���
		_brawler->attack(_angle);

		_brawler->castAbility(_angle);
	}
}

//������Ϣ
void AI::update1s(float dt)
{
	//�����������Ϣ������������
	updateNearestBrawler();
	updateNearestBox();
	updateNearestBuff();

	//����Ŀ�ĵ�
	float vision = 500;	//�Ӿ�
	Vec2 pos = getPosition();
	Vec2 otherPos = _nearestBrawler->getParent()->getPosition();
	if (vision < otherPos.getDistance(getPosition()) || _nearestBrawler->getInBush())
	{
		//�����Ӿ��ڣ�ֱ������Ӣ�ۣ�ǰ��buff/����
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
		//���Ӿ��ڣ�ֱ�ӿ�ɱ
		_destination = otherPos;
		_target = _nearestBrawler;
		_targetPos = _nearestBrawler->getParent()->getPosition();
	}

	//����Ŀ��Ƕ�
	if (fabs(_targetPos.x - pos.x) < 1e-6 && _targetPos.y >= pos.y)
		_angle = M_PI / 2;
	else if (fabs(_targetPos.x - pos.x) < 1e-6 && _targetPos.y < pos.y)
		_angle = -M_PI / 2;
	else
		_angle = atan((_targetPos.y - pos.y) / (_targetPos.x - pos.x));

	/*�Ƕ�����*/
	if (_targetPos.x < pos.x)
		_angle += M_PI;
}

//��ȡ�����Ӣ��
void AI::updateNearestBrawler()
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	//��ȡ���������Ӣ��
	Vector<Brawler*> brawlerVec = GameScene::getGameScene()->getBrawlerVector();
	for (int i = 0; i < brawlerVec.size(); i++)
	{
		//��ȥ�Լ�
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

//��ȡ����ı���
void AI::updateNearestBox()
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	//��ȡ��������ı���
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

//��ȡ�����buff
void AI::updateNearestBuff()
{
	Vec2 pos = getPosition();
	float minDistance = INT_MAX;
	int index = 0;

	//��ȡ���������buff
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