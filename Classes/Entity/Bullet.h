#ifndef __BULLET_H_
#define __BULLET_H_

#include "cocos2d.h"

USING_NS_CC;

class Entity;
class Brawler;
class Bullet : public Entity {
	/*����*/
	CC_SYNTHESIZE(Brawler*, _launcher, Launcher);//������
	CC_SYNTHESIZE(float, _range, Range);		//���

public:
	/*���캯��*/
	Bullet();

	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Bullet);
	virtual bool init();

	/*�Զ�������*/
	void setAttributes(INT32 attackDamage, INT32 moveSpeed, float range, Brawler* launcher);

	void launch(Vec2 direction);      //����һ���ǶȲ�������÷������ȥ
	void collide(Entity* target);     //����һ��Entity��������ײʱ����
};

#endif// __BULLET_H_