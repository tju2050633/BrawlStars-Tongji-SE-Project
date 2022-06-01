#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Entity/Bullet.h"

USING_NS_CC;

class Brawler : public Entity {
	/*����*/
	CC_SYNTHESIZE(INT32, _ammo, Ammo);//��ҩ
	CC_SYNTHESIZE(INT32, _energyBar, EnergyBar);//���������ͷŴ����ã�

	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //��ǰx�����ٶ�
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //��ǰy�����ٶ�

	/*�ѷ�����ӵ�*/
	Vector<Bullet*> _bulletVector;

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Brawler);
	virtual bool init();

	void update(float dt)override;

	/*�̳���Entity�ĺ���*/
	void die();  //����

	/*Brawler���к���*/
	virtual void castAbility(float angle) {}
	void takeBuff();               //���buff����������
	
};

#endif// !__BRAWLER_H_