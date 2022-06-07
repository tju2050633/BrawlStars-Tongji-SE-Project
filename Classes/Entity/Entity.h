#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "cocos2d.h"


USING_NS_CC;


class Entity : public Node {
	/*����*/
	CC_SYNTHESIZE(bool, _isPlayer, IsPlayer);						//����Ҳ��ݵ�Ӣ��
	CC_SYNTHESIZE(bool, _isAI, IsAI);								//��AI

	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);						//����
	CC_SYNTHESIZE(Sprite*, _hpBar, HpBar);							//Ѫ��
	CC_SYNTHESIZE(Size, _hpBarSize, HpBarSize);						//Ѫ���ߴ�
	CC_SYNTHESIZE(Label*, _hpBarLabel, HpBarLabel);					//Ѫ������
	CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);				//Ѫ��
	CC_SYNTHESIZE(INT32, _currentHealthPoint, CurrentHealthPoint);  //��ǰѪ��
	CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);				//������
	CC_SYNTHESIZE(bool, _isAttackAvailable, IsAttackAvailable);		//������
	CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);					//����
	CC_SYNTHESIZE(float, _attackInterval, AttackInterval);			//�������
public:
	/*���캯�� ��������*/
	Entity();
	virtual ~Entity();

	/*�󶨾���*/
	void bindSprite(Sprite* sprite);

	void setHpBarPercent(float percent);	//����Ѫ���ٷֱ�
	static void initHpBar(Entity* target);			//��ʼ��Ѫ��

	virtual void attack(float angle) {}  //����
	virtual bool takeDamage(INT32 damage);  //�����˺�
	virtual void die();  //����
};

#endif// !__ENTITY_H_