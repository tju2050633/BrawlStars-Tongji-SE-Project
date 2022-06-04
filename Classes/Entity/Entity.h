#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Entity : public Node {
	/*属性*/
	CC_SYNTHESIZE(Layer*, _gameScene, GameScene);					//所处场景
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);						//精灵
	CC_SYNTHESIZE(Sprite*, _hpBar, HpBar);							//血条
	CC_SYNTHESIZE(Size, _hpBarSize, HpBarSize);						//血条尺寸
	CC_SYNTHESIZE(Label*, _hpBarLabel, HpBarLabel);					//血条文字
	CC_SYNTHESIZE(INT32, _healthPoint, HealthPoint);				//血量
	CC_SYNTHESIZE(INT32, _currentHealthPoint, CurrentHealthPoint);  //当前血量
	CC_SYNTHESIZE(INT32, _attackDamage, AttackDamage);				//攻击力
	CC_SYNTHESIZE(INT32, _moveSpeed, MoveSpeed);					//移速
	CC_SYNTHESIZE(float, _attackInterval, AttackInterval);			//攻击间隔
public:
	/*构造函数 析构函数*/
	Entity();
	virtual ~Entity();

	void setHpBarPercent(float percent);	//设置血条百分比

	virtual void attack(float angle) {}  //攻击
	virtual void takeDamage(INT32 damage);  //承受伤害
	virtual void die() {}  //死亡
};

#endif// !__ENTITY_H_