#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity : public Node {
	/*����*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);          //����
	CC_SYNTHESIZE(Sprite*, _hpBar, HpBar);      //Ѫ�����
	CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);  //Ѫ��
	CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);//������
	CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);      //����
	CC_SYNTHESIZE(float, _attackInterval, AttackInterval);  //�������
	CC_SYNTHESIZE(bool, _inBush, InBush);           //�ж��Ƿ��ڲݴ���
private:

public:
	/*���캯�� ��������*/
	Entity();
	virtual ~Entity();

	/*�󶨾���*/
	void bindSprite(Sprite* sprite);
	/*��Ѫ��*/
	void bindHpBar(Sprite* hpBar);

	virtual void attack(float angle) {}  //����
	virtual void die() {}  //����
	void takeDamage(INT32 damage);  //�����˺�
};

#endif// !__ENTITY_H_