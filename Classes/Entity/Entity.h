#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity : public Node {
	/*����*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);          //����
	CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);  //Ѫ��
	CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);//������
	CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);      //����
	CC_SYNTHESIZE(float, _attackInterval, AttackInterval);  //�������
	CC_SYNTHESIZE(bool, _inBush, InBush);           //�ж��Ƿ��ڲݴ���
	CC_SYNTHESIZE(Sprite*, _hpBar, HpBar);      //Ѫ�����
	//����ķ���
private:

public:
	/*���캯�� ��������*/
	Entity();
	virtual ~Entity();

	/*�󶨾���*/
	void bindSprite(Sprite* sprite);

	virtual void attack() {}  //����
	void takeDamage(INT32 damage);  //�����˺�
	virtual void move() {}  //�ƶ�
	virtual void die() {}  //����
};

#endif// !__ENTITY_H_