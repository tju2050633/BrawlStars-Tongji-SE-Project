#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Brawler : public Entity {
	/*����*/
	CC_SYNTHESIZE(INT32, _ammo, Ammo);//��ҩ
	CC_SYNTHESIZE(INT32, _energyBar, EnergyBar);//���������ͷŴ����ã�

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Brawler);
	virtual bool init();

	/*�̳���Entity�ĺ���*/
	void move();  //�ƶ�
	void die();  //����

	/*Brawler���к���*/
	void takeBuff();               //���buff����������
	
};

#endif// !__BRAWLER_H_