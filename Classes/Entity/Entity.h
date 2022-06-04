#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Entity : public Node {
	/*����*/
	CC_SYNTHESIZE(Layer*, _gameScene, GameScene);					//��������
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);						//����
	CC_SYNTHESIZE(Sprite*, _hpBar, HpBar);							//Ѫ��
	CC_SYNTHESIZE(Size, _hpBarSize, HpBarSize);						//Ѫ���ߴ�
	CC_SYNTHESIZE(Label*, _hpBarLabel, HpBarLabel);					//Ѫ������
	CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);				//Ѫ��
	CC_SYNTHESIZE(INT32, _currentHealthPoint, CurrentHealthPoint);  //��ǰѪ��
	CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);				//������
	CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);					//����
	CC_SYNTHESIZE(float, _attackInterval, AttackInterval);			//�������
public:
	/*���캯�� ��������*/
	Entity();
	virtual ~Entity();

	void setHpBarPercent(float percent);	//����Ѫ���ٷֱ�

	virtual void attack(float angle) {}  //����
	virtual void takeDamage(INT32 damage);  //�����˺�
	virtual void die() {}  //����
};

#endif// !__ENTITY_H_