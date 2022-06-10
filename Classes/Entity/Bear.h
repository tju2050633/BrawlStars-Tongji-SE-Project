#ifndef __BEAR_H_
#define __BEAR_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Brawler;
class Bear : public Entity{
	CC_SYNTHESIZE(Brawler*, _owner, Owner);//����
	CC_SYNTHESIZE(INT32, _attackRange, AttackRange); //��������

	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //��ǰx�����ٶ�
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //��ǰy�����ٶ�

	CC_SYNTHESIZE(Brawler*, _target, Target);				//Ŀ��Ӣ��
	CC_SYNTHESIZE(Vec2, _targetPos, TargetPos);				//Ŀ������

	bool _X_Direction_Modity;	//X�����ٶ�������trueΪ��x����
	bool _Y_Direction_Modity;	//Y�����ٶ�������trueΪ��y����

	bool _animationAvailable;	//��ֹ��������̫Ƶ��
	bool _isAvoidingWall;		//��ֹ�ٶ�����̫Ƶ��

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Bear);
	virtual bool init();

	void update(float dt);
	void update05s(float dt);
	void update1s(float dt);

	void updateMoveSpeed();

	void attack(Brawler* brawler);
	void die()override;
};

#endif// !__BEAR_H_