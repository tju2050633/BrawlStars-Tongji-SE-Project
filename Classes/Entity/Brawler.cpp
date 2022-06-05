#include <cmath>
#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Utils/SceneUtils.h"
#include "Scene/GameScene.h"

bool Brawler::init()
{
	_ammo = 3;
	_energy = 0;
	_moveSpeedX = 0;
	_moveSpeedY = 0;

	_isCastingAbility = false;

	this->scheduleUpdate();
	this->schedule([&](float dt) {
		if (_ammo >= 3)
		{
			unschedule("reload");
			return;
		}
		_ammo++;
		setAmmoBarPercent(float(_ammo) / 3);
	}, 1.5f, "reload");	//刷新弹药

	return true;
}

void Brawler::update(float dt)
{
	/*遍历已发射子弹，每帧进行移动*/
	for (int i = 0;i < _bulletVector.size();i++)
	{
		auto bullet = _bulletVector.at(i);
		auto bulletPosition = bullet->getPosition() 
			+ this->getParent()->getPosition();//在地图上的坐标
		//位置要合法
		auto pos = GameScene::getGameScene()->tileCoordForPosition(bulletPosition);
		if (!(pos.x < 47 && pos.y < 37 && pos.x >= 3 && pos.y >= 3))
		{
			_bulletVector.erase(i);
			removeChild(bullet, true);
			continue;
		}
		//子弹每帧移动量
		float angle = bullet->getAngle();					
		float dx = (bullet->getSpeed() * cos(angle) - _moveSpeedX) * dt;	
		float dy = (bullet->getSpeed() * sin(angle) - _moveSpeedY) * dt;
		//若达到射程，移除子弹
		bullet->setDistance(bullet->getDistance() + bullet->getSpeed() * dt);
		if (bullet->getDistance() >= bullet->getRange())
		{
			_bulletVector.erase(i);
			removeChild(bullet, true);
			continue;
		}
		//碰到墙体，攻击的子弹移除，技能的子弹摧毁墙体后移除
		if (GameScene::getGameScene()->isWallTile(bulletPosition))
		{
			
			if (bullet->getIsAbility())
				GameScene::getGameScene()->breakWall(bulletPosition);

			_bulletVector.erase(i);
			removeChild(bullet, true);
			continue;
		}
		//碰到实体，技能子弹将其击退一段距离，子弹移除
		
		//继续移动
		bullet->setPosition(bullet->getPosition() + Vec2(dx, dy));
	}
}

/*攻击*/
void Brawler::attack(float angle)
{
	/*重置恢复状态*/
	resetReadyForHeal();

	/*若弹药为满，重新开始定时器*/
	if (_ammo >= 3) {
		this->schedule([&](float dt) {
			if (_ammo >= 3)
			{
				unschedule("reload");
				return;
			}
			_ammo++;
			setAmmoBarPercent(float(_ammo) / 3);
		}, 1.5f, "reload");	//刷新弹药
	}

	_ammo--;
	setAmmoBarPercent(float(_ammo) / 3);
}

/*受伤*/
void Brawler::takeDamage(INT32 damage)
{
	/*调用父类函数*/
	Entity::takeDamage(damage);

	/*重置恢复状态*/
	resetReadyForHeal();
}

/*死亡*/
void Brawler::die()
{
	/*英雄数-1，配合GameScene的update刷新Label内容和出毒圈、换BGM、判定胜利等*/
	SceneUtils::_brawlerNumber--;
}

/*造成伤害*/
void Brawler::dealDamage(INT32 damage)
{
	/*增加能量*/
	INT32 energy = min(_energy + damage, _maxEnergy);
	setEnergy(energy);

	/*能量条*/
	setEnergeBarPercent(float(_energy) / _maxEnergy);

	/*如果能量已满，改变技能图标*/
	if (_energy == _maxEnergy)
	{
		_playerController->getAbilityCenterSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AbilityCenter.png"));//
		if (_playerController->getAbilityRoundSprite()->isVisible() == false)
			_playerController->getAbilityCenterSprite()->setPosition(_playerController->getAbilityCenterSprite()->getPosition() + Vec2(45, 85));//
		_playerController->getAbilityRoundSprite()->setVisible(true);//
	}
}

/*技能*/
void Brawler::castAbility(float angle)
{
	/*重置恢复状态*/
	resetReadyForHeal();
}

/*获得buff，增加属性*/
void Brawler::takeBuff()
{
	/*加血量*/
	_healthPoint += 400;
	_currentHealthPoint += 400;
	setHpBarPercent(float(_currentHealthPoint) / _healthPoint);

	/*加伤害*/
	_attackDamage *= 1.1;
}

/*治疗*/
void Brawler::heal(INT32 healAmount)
{
	/*回血，不超过满血*/
	INT32 hp = min(getCurrentHealthPoint() + healAmount, getHealthPoint());
	setCurrentHealthPoint(hp);

	/*设置血条*/
	setHpBarPercent(float(_currentHealthPoint) / _healthPoint);

	/*血条文字*/
	getHpBarLabel()->setString(StringUtils::format("%d", _currentHealthPoint));
}

/*攻击、放技能、受伤，重置距离恢复时间*/
void Brawler::resetReadyForHeal()
{
	setReadyForHeal(false);
	unschedule("heal");
	schedule([&](float dt) {
		setReadyForHeal(true);
		}, 5.0f, "heal");
}

/*设置弹药条百分比*/
void Brawler::setAmmoBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getAmmoBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ammoBar.png"),
		Rect(0, 0, _ammoBarSize.width * percent, _ammoBarSize.height)));
}

/*设置能量条百分比*/
void Brawler::setEnergeBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getEnergyBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("energyBar.png"),
		Rect(0, 0, _energyBarSize.width * percent, _energyBarSize.height)));
}