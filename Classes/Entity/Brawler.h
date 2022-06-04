#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Entity/Bullet.h"
#include "Utils/AnimationUtils.h"
#include "Controller/PlayerController.h"

USING_NS_CC;

class Brawler : public Entity {
	/*������*/
	CC_SYNTHESIZE(bool, _isPlayer, IsPlayer);								//����Ҳ��ݵ�Ӣ��
	CC_SYNTHESIZE(PlayerController* , _playerController, PlayerController);	//������

	/*����*/
	CC_SYNTHESIZE(INT32, _ammo, Ammo);			//��ҩ
	CC_SYNTHESIZE(Sprite*, _ammoBar, AmmoBar);	//��ҩ��
	CC_SYNTHESIZE(Size, _ammoBarSize, AmmoBarSize);//��ҩ���ߴ�
	CC_SYNTHESIZE(INT32, _energy, Energy);		//��ǰ����
	CC_SYNTHESIZE(INT32, _maxEnergy, MaxEnergy);//�������
	CC_SYNTHESIZE(Sprite*, _energyBar, EnergyBar);//������
	CC_SYNTHESIZE(Size, _energyBarSize, EnergyBarSize);//�������ߴ�

	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //��ǰx�����ٶ�
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //��ǰy�����ٶ�

	/*�ѷ�����ӵ�*/
	Vector<Bullet*> _bulletVector;

	/*��Χָʾ��*/
	CC_SYNTHESIZE(Sprite*, _rangeIndicatorAttack, RangeIndicatorAttack);
	CC_SYNTHESIZE(Sprite*, _rangeIndicatorAbility, RangeIndicatorAbility);

	/*������Ҫ��Ӣ��ö����*/
	CC_SYNTHESIZE(AnimationUtils::BrawlerEnum, _animateBrawler, AnimateBrawler);

	/*�����ϴι��������˹�ȥ5s�����Ի�Ѫ*/
	CC_SYNTHESIZE(bool, _readyForHeal, ReadyForHeal);

public:
	/*��������ͳ�ʼ������*/
	CREATE_FUNC(Brawler);
	virtual bool init();

	void update(float dt)override;

	/*�̳���Entity�ĺ���*/
	virtual void attack(float angle)override;	//����
	
	virtual void takeDamage(INT32 damage)override;//����
	virtual void die()override;					//����

	/*Brawler���к���*/
	void dealDamage(INT32 damage);			//����˺�
	virtual void castAbility(float angle);	//����
	void takeBuff();						//���buff����������
	void heal(INT32 healAmount);			//����
	void resetReadyForHeal();				//�������ż��ܡ����ˣ����þ���ָ�ʱ��

	void setAmmoBarPercent(float percent);		//���õ�ҩ���ٷֱ�
	void setEnergeBarPercent(float percent);	//�����������ٷֱ�
};

#endif// !__BRAWLER_H_