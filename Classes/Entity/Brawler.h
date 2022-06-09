#ifndef __BRAWLER_H_
#define __BRAWLER_H_

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "Entity/Bullet.h"
#include "Utils/AnimationUtils.h"
#include "Controller/PlayerController.h"
#include "Entity/Bear.h"

USING_NS_CC;

class Brawler : public Entity {
	/*玩家相关*/
	CC_SYNTHESIZE(PlayerController*, _playerController, PlayerController);	//操作器

	/*属性*/
	CC_SYNTHESIZE(INT32, _ammo, Ammo);			//弹药
	CC_SYNTHESIZE(Sprite*, _ammoBar, AmmoBar);	//弹药条
	CC_SYNTHESIZE(Size, _ammoBarSize, AmmoBarSize);//弹药条尺寸
	CC_SYNTHESIZE(INT32, _energy, Energy);		//当前能量
	CC_SYNTHESIZE(INT32, _maxEnergy, MaxEnergy);//最大能量
	CC_SYNTHESIZE(Sprite*, _energyBar, EnergyBar);//能量条
	CC_SYNTHESIZE(Size, _energyBarSize, EnergyBarSize);//能量条尺寸
	CC_SYNTHESIZE(INT32, _buffNumber, BuffNumber);//buff数量
	CC_SYNTHESIZE(Label*, _buffLabel, BuffLabel);//buff文字标签

	CC_SYNTHESIZE(INT32, _moveSpeedX, MoveSpeedX); //当前x方向速度
	CC_SYNTHESIZE(INT32, _moveSpeedY, MoveSpeedY); //当前y方向速度

	CC_SYNTHESIZE(bool, _isCastingAbility, IsCastingAbility); //正在放技能，无法操纵移动
	CC_SYNTHESIZE(bool, _keysReleased, KeysReleased);		 //WASD全部释放

	/*已发射的子弹*/
	Vector<Bullet*> _bulletVector;

	/*范围指示器*/
	CC_SYNTHESIZE(Sprite*, _rangeIndicatorAttack, RangeIndicatorAttack);
	CC_SYNTHESIZE(Sprite*, _rangeIndicatorAbility, RangeIndicatorAbility);

	/*动画需要的英雄枚举类*/
	CC_SYNTHESIZE(AnimationUtils::EntityEnum, _animateBrawler, AnimateBrawler);

	/*距离上次攻击或受伤过去5s，可以回血*/
	CC_SYNTHESIZE(bool, _readyForHeal, ReadyForHeal);

	/*Nita的熊*/
	CC_SYNTHESIZE(Bear*, _bear, Bear);

public:
	/*创建对象和初始化函数*/
	CREATE_FUNC(Brawler);
	virtual bool init();

	void update(float dt)override;

	/*继承自Entity的函数*/
	virtual void attack(float angle)override;	//攻击
	virtual bool takeDamage(INT32 damage)override;//受伤
	virtual void die()override;					//死亡

	/*Brawler特有函数*/
	void dealDamage(INT32 damage);			//造成伤害
	void kill(Brawler* brawler);			//击杀英雄
	virtual void castAbility(float angle);	//技能
	void takeBuff();						//获得buff，增加属性
	void heal(INT32 healAmount);			//治疗
	void resetReadyForHeal();				//攻击、放技能、受伤，重置距离恢复时间

	void setAmmoBarPercent(float percent);		//设置弹药条百分比
	void setEnergeBarPercent(float percent);	//设置能量条百分比

	AnimationUtils::TypeEnum getDirection();    //获取英雄朝向
};

#endif// !__BRAWLER_H_