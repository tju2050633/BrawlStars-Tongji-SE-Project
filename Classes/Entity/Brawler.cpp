#include <cmath>
#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Utils/SceneUtils.h"
#include "Utils/AnimationUtils.h"
#include "Scene/GameScene.h"
#include "Constant/Const.h"

bool Brawler::init()
{
	//属性初始化
	_ammo = 3;
	_energy = 0;
	_moveSpeedX = 0;
	_moveSpeedY = 0;
	_buffNumber = 0;

	_isCastingAbility = false;
	_keysReleased = true;

	//添加进GameScene的数组
	GameScene::getGameScene()->pushBackBrawler(this);
		
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
	for (int i = 0; i < _bulletVector.size(); i++)
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
		
		Vector<Brawler*> brawlerVec = GameScene::getGameScene()->getBrawlerVector();
		Vector<Entity*> entityVec = GameScene::getGameScene()->getEntityVector();

		bool isCollided = false;//子弹已与英雄/熊/宝箱发生碰撞
		//碰到英雄
		for (int j = 0; j < brawlerVec.size(); j++)
		{
			auto bullet_pos_to_target = bulletPosition - brawlerVec.at(j)->getPosition();//子弹相对目标物的位置
			if (brawlerVec.at(j) == this)//不能攻击自身
				continue;
			Rect rect = brawlerVec.at(j)->getSprite()->getBoundingBox();
			float scale = entityVec.at(j)->getScale();//碰撞体积是精灵图原始大小，要乘以实体scale
			Size size = rect.size * scale;
			rect.setRect(rect.getMinX() * scale, rect.getMinY() * scale, size.width, size.height);
			if (rect.containsPoint(bullet_pos_to_target))
			{
				//shelly技能可将英雄击退
				if (bullet->getIsAbility())
				{
					int distance = SHELLY_BEAT_DISTANCE;
					float angle = bullet->getAngle();
					brawlerVec.at(j)->getParent()->runAction(MoveBy::create(1.0f, Vec2(distance * cos(angle), distance * cos(angle))));
				}
				bullet->collideWithBrawler(brawlerVec.at(j));
				_bulletVector.erase(i);
				isCollided = true;
				break;
			}
		}
		if (isCollided)
			continue;
		//碰到熊或宝箱
		for (int j = 0; j < entityVec.size(); j++)
		{
			auto bullet_pos_to_target = bulletPosition - entityVec.at(j)->getPosition();//子弹相对目标物的位置
			//if (entityVec.at(j) == _bear)//不能攻击自己的熊
			//	continue;
			Rect rect = entityVec.at(j)->getSprite()->getBoundingBox();
			float scale = entityVec.at(j)->getScale();//碰撞体积是精灵图原始大小，要乘以实体scale
			Size size = rect.size * scale;
			rect.setRect(rect.getMinX() * scale, rect.getMinY() * scale, size.width, size.height);
			if (rect.containsPoint(bullet_pos_to_target))
			{
				bullet->collideWithEntity(entityVec.at(j));
				_bulletVector.erase(i);
				isCollided = true;
				break;
			}
		}
		if (isCollided)
			continue;

		//继续移动
		bullet->setPosition(bullet->getPosition() + Vec2(dx, dy));
	}

	/*监测位置，获取buff*/
	auto buffVec = GameScene::getGameScene()->getBuffVector();
	auto playerPos = this->getParent()->getPosition();
	for (int i = 0; i < buffVec.size(); i++)
	{
		auto buff = buffVec.at(i);
		Rect rect = buff->getBoundingBox();
		if (rect.containsPoint(playerPos))
		{
			this->takeBuff();
			buff->removeFromParent();
			GameScene::getGameScene()->removeFromBuffVector(buff);
			break;
		}
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
bool Brawler::takeDamage(INT32 damage)
{
	/*重置恢复状态*/
	resetReadyForHeal();

	/*调用父类函数*/
	return Entity::takeDamage(damage);
}

/*死亡*/
void Brawler::die()
{
	/*通知GameScene*/
	GameScene::getGameScene()->BrawlerDie();

	/*玩家死亡，失败，隐藏节点;否则,若仅剩一个英雄，胜利，其他英雄直接移除*/
	if (_isPlayer)
	{
		setVisible(false);
		GameScene::getGameScene()->GameOver(false);
	}
	else
	{
		/*掉落buff*/
		auto buff = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Buff.png"));
		buff->setPosition(getPosition());
		getParent()->addChild(buff, 1);

		/*移除*/
		removeFromParent();
		GameScene::getGameScene()->removeFromBrawlerVector(this);


		if (SceneUtils::_brawlerNumber == 1)
			GameScene::getGameScene()->GameOver(true);
	}
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

/*击杀英雄*/
void Brawler::kill(Brawler* brawler)
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*获取英雄名*/
	string leftBrawlerName;
	string rightBrawlerName;

	leftBrawlerName = AnimationUtils::Entities[_animateBrawler];
	rightBrawlerName = AnimationUtils::Entities[brawler->getAnimateBrawler()];

	/*飘出击杀提示*/
	auto info = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Notice.png"));
	auto left = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/" + leftBrawlerName + "-Normal.png"));
	auto right = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/" + rightBrawlerName + "-Normal.png"));

	left->setScale(0.2);
	left->setPosition(Vec2(160,90));

	right->setScale(0.2);
	right->setPosition(Vec2(325,90));

	info->addChild(left);
	info->addChild(right);
	info->setScale(0.8);
	info->setAnchorPoint(Vec2(1, 1));
	info->setPosition(Vec2(origin.x, origin.y + visibleSize.height - 100));
	GameScene::getGameScene()->getUILayer()->addChild(info, 1);

	auto move = MoveBy::create(0.3, Vec2(250, 0));
	auto delay = MoveBy::create(1.5, Vec2(1, 0));
	auto vanish = CallFunc::create([=]() {
		info->removeFromParent();
		});

	auto sequence = Sequence::create(move, delay, vanish, NULL);

	info->runAction(sequence);
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
	heal(400);
	setHpBarPercent(float(_currentHealthPoint) / _healthPoint);

	/*加伤害*/
	_attackDamage *= 1.1;

	/*修改buff文字标签*/
	_buffNumber++;
	_buffLabel->setString(StringUtils::format("%d", _buffNumber).c_str());
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

/*获取英雄朝向*/
AnimationUtils::TypeEnum Brawler::getDirection()
{
	if (_moveSpeedY>0)
	{
		return AnimationUtils::Top;
	}
	else if (_moveSpeedY < 0)
	{
		return AnimationUtils::Bottom;
	}
	else if (_moveSpeedX > 0)
	{
		return AnimationUtils::Right;
	}
	else if (_moveSpeedX < 0)
	{
		return AnimationUtils::Left;
	}
}