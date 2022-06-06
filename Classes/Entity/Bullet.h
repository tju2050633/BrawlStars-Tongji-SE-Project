#ifndef __BULLET_H_
#define __BULLET_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity;
class Brawler;
class Bullet : public Node {
	/*����*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);     //����
	CC_SYNTHESIZE(Brawler*, _launcher, Launcher);//������
	CC_SYNTHESIZE(INT32, _damage, Damage);		//�˺�
	CC_SYNTHESIZE(INT32, _speed, Speed);		//�ٶ�
	CC_SYNTHESIZE(float, _range, Range);		//���
	CC_SYNTHESIZE(float, _distance, Distance);	//���߹�����
	CC_SYNTHESIZE(float, _angle, Angle);		//�Ƕ�
	CC_SYNTHESIZE(bool, _isAbility, IsAbility);	//�Ǽ��ܵ��ӵ�

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Bullet);
	virtual bool init();

	/*�󶨾���*/
	void bindSprite(Sprite* sprite);

	/*��������*/
	void setAttributes(INT32 damage, INT32 speed, INT32 range, float angle, Brawler* launcher);

	void collideWithBrawler(Brawler* target);     //��ײӢ��
	void collideWithEntity(Entity* target);     //��ײ�ܡ�����
};

#endif// __BULLET_H_