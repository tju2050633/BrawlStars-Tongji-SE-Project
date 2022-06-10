#ifndef __AI_H_
#define __AI_H_

#include "cocos2d.h"

USING_NS_CC;
class Brawler;
class Entity;
class AI :public Node {
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //���ݵ�Ӣ��
	CC_SYNTHESIZE(INT32, _attackRange, AttackRange); //��������

	CC_SYNTHESIZE(Entity*, _nearestBox, NearestBox);			//����ı���
	CC_SYNTHESIZE(Sprite*, _nearestBuff, NearestBuff);			//�����buff
	CC_SYNTHESIZE(Brawler*, _nearestBrawler, _nearestBrawler);	//�����Ӣ��
	CC_SYNTHESIZE(Vec2, _destination, Destination);				//Ŀ�ĵ�
	CC_SYNTHESIZE(Entity*, _target, Target);					//Ŀ�꣬���䡢׷ɱ��Ӣ�ۣ�Ϊ��ʱ����
	CC_SYNTHESIZE(Vec2, _targetPos, TargetPos);					//Ŀ������
	CC_SYNTHESIZE(float, _angle, Angle);					//Ŀ��ĽǶ�

	bool _X_Direction_Modity;	//X�����ٶ�������trueΪ��x����
	bool _Y_Direction_Modity;	//Y�����ٶ�������trueΪ��y����

	bool _animationAvailable;	//��ֹ��������̫Ƶ��
	bool _isAvoidingWall;		//��ֹ�ٶ�����̫Ƶ��

public:
	CREATE_FUNC(AI);
	virtual bool init();
	virtual void update(float dt);//ÿ֡ˢ�£��ı�����
	void updateMoveSpeed();	//ˢ������
	void updateBushVisibility();	//ˢ�²ݴ���Ұ���
	void update05s(float dt);	//ÿ0.5��ˢ�£�������Ϊ
	void update1s(float dt);	//ÿ��ˢ�£�����Ŀ�ꡢ����ı���

	void updateNearestBrawler();
	void updateNearestBox();
	void updateNearestBuff();

};

#endif // !__AI_H_
