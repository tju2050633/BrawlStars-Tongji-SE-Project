#include <cmath>
#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Utils/SceneUtils.h"
#include "Utils/AnimationUtils.h"
#include "Scene/GameScene.h"
#include "Constant/Const.h"

bool Brawler::init()
{
	//���Գ�ʼ��
	_ammo = 3;
	_energy = 0;
	_moveSpeedX = 0;
	_moveSpeedY = 0;
	_buffNumber = 0;

	_isCastingAbility = false;
	_keysReleased = true;

	//��ӽ�GameScene������
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
		}, 1.5f, "reload");	//ˢ�µ�ҩ

	return true;
}

void Brawler::update(float dt)
{
	/*�����ѷ����ӵ���ÿ֡�����ƶ�*/
	for (int i = 0; i < _bulletVector.size(); i++)
	{
		auto bullet = _bulletVector.at(i);
		auto bulletPosition = bullet->getPosition()
			+ this->getParent()->getPosition();//�ڵ�ͼ�ϵ�����
		//λ��Ҫ�Ϸ�
		auto pos = GameScene::getGameScene()->tileCoordForPosition(bulletPosition);
		if (!(pos.x < 47 && pos.y < 37 && pos.x >= 3 && pos.y >= 3))
		{
			_bulletVector.erase(i);
			removeChild(bullet, true);
			continue;
		}
		//�ӵ�ÿ֡�ƶ���
		float angle = bullet->getAngle();
		float dx = (bullet->getSpeed() * cos(angle) - _moveSpeedX) * dt;
		float dy = (bullet->getSpeed() * sin(angle) - _moveSpeedY) * dt;
		//���ﵽ��̣��Ƴ��ӵ�
		bullet->setDistance(bullet->getDistance() + bullet->getSpeed() * dt);
		if (bullet->getDistance() >= bullet->getRange())
		{
			_bulletVector.erase(i);
			removeChild(bullet, true);
			continue;
		}
		//����ǽ�壬�������ӵ��Ƴ������ܵ��ӵ��ݻ�ǽ����Ƴ�
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

		bool isCollided = false;//�ӵ�����Ӣ��/��/���䷢����ײ
		//����Ӣ��
		for (int j = 0; j < brawlerVec.size(); j++)
		{
			auto bullet_pos_to_target = bulletPosition - brawlerVec.at(j)->getPosition();//�ӵ����Ŀ�����λ��
			if (brawlerVec.at(j) == this)//���ܹ�������
				continue;
			Rect rect = brawlerVec.at(j)->getSprite()->getBoundingBox();
			float scale = entityVec.at(j)->getScale();//��ײ����Ǿ���ͼԭʼ��С��Ҫ����ʵ��scale
			Size size = rect.size * scale;
			rect.setRect(rect.getMinX() * scale, rect.getMinY() * scale, size.width, size.height);
			if (rect.containsPoint(bullet_pos_to_target))
			{
				//shelly���ܿɽ�Ӣ�ۻ���
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
		//�����ܻ���
		for (int j = 0; j < entityVec.size(); j++)
		{
			auto bullet_pos_to_target = bulletPosition - entityVec.at(j)->getPosition();//�ӵ����Ŀ�����λ��
			//if (entityVec.at(j) == _bear)//���ܹ����Լ�����
			//	continue;
			Rect rect = entityVec.at(j)->getSprite()->getBoundingBox();
			float scale = entityVec.at(j)->getScale();//��ײ����Ǿ���ͼԭʼ��С��Ҫ����ʵ��scale
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

		//�����ƶ�
		bullet->setPosition(bullet->getPosition() + Vec2(dx, dy));
	}

	/*���λ�ã���ȡbuff*/
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

/*����*/
void Brawler::attack(float angle)
{
	/*���ûָ�״̬*/
	resetReadyForHeal();

	/*����ҩΪ�������¿�ʼ��ʱ��*/
	if (_ammo >= 3) {
		this->schedule([&](float dt) {
			if (_ammo >= 3)
			{
				unschedule("reload");
				return;
			}
			_ammo++;
			setAmmoBarPercent(float(_ammo) / 3);
			}, 1.5f, "reload");	//ˢ�µ�ҩ
	}

	_ammo--;
	setAmmoBarPercent(float(_ammo) / 3);
}

/*����*/
bool Brawler::takeDamage(INT32 damage)
{
	/*���ûָ�״̬*/
	resetReadyForHeal();

	/*���ø��ຯ��*/
	return Entity::takeDamage(damage);
}

/*����*/
void Brawler::die()
{
	/*֪ͨGameScene*/
	GameScene::getGameScene()->BrawlerDie();

	/*���������ʧ�ܣ����ؽڵ�;����,����ʣһ��Ӣ�ۣ�ʤ��������Ӣ��ֱ���Ƴ�*/
	if (_isPlayer)
	{
		setVisible(false);
		GameScene::getGameScene()->GameOver(false);
	}
	else
	{
		/*����buff*/
		auto buff = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Buff.png"));
		buff->setPosition(getPosition());
		getParent()->addChild(buff, 1);

		/*�Ƴ�*/
		removeFromParent();
		GameScene::getGameScene()->removeFromBrawlerVector(this);


		if (SceneUtils::_brawlerNumber == 1)
			GameScene::getGameScene()->GameOver(true);
	}
}

/*����˺�*/
void Brawler::dealDamage(INT32 damage)
{
	/*��������*/
	INT32 energy = min(_energy + damage, _maxEnergy);
	setEnergy(energy);

	/*������*/
	setEnergeBarPercent(float(_energy) / _maxEnergy);

	/*��������������ı似��ͼ��*/
	if (_energy == _maxEnergy)
	{
		_playerController->getAbilityCenterSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AbilityCenter.png"));//
		if (_playerController->getAbilityRoundSprite()->isVisible() == false)
			_playerController->getAbilityCenterSprite()->setPosition(_playerController->getAbilityCenterSprite()->getPosition() + Vec2(45, 85));//
		_playerController->getAbilityRoundSprite()->setVisible(true);//
	}
}

/*��ɱӢ��*/
void Brawler::kill(Brawler* brawler)
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*��ȡӢ����*/
	string leftBrawlerName;
	string rightBrawlerName;

	leftBrawlerName = AnimationUtils::Entities[_animateBrawler];
	rightBrawlerName = AnimationUtils::Entities[brawler->getAnimateBrawler()];

	/*Ʈ����ɱ��ʾ*/
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

/*����*/
void Brawler::castAbility(float angle)
{
	/*���ûָ�״̬*/
	resetReadyForHeal();
}

/*���buff����������*/
void Brawler::takeBuff()
{
	/*��Ѫ��*/
	_healthPoint += 400;
	heal(400);
	setHpBarPercent(float(_currentHealthPoint) / _healthPoint);

	/*���˺�*/
	_attackDamage *= 1.1;

	/*�޸�buff���ֱ�ǩ*/
	_buffNumber++;
	_buffLabel->setString(StringUtils::format("%d", _buffNumber).c_str());
}

/*����*/
void Brawler::heal(INT32 healAmount)
{
	/*��Ѫ����������Ѫ*/
	INT32 hp = min(getCurrentHealthPoint() + healAmount, getHealthPoint());
	setCurrentHealthPoint(hp);

	/*����Ѫ��*/
	setHpBarPercent(float(_currentHealthPoint) / _healthPoint);

	/*Ѫ������*/
	getHpBarLabel()->setString(StringUtils::format("%d", _currentHealthPoint));
}

/*�������ż��ܡ����ˣ����þ���ָ�ʱ��*/
void Brawler::resetReadyForHeal()
{
	setReadyForHeal(false);
	unschedule("heal");
	schedule([&](float dt) {
		setReadyForHeal(true);
		}, 5.0f, "heal");
}

/*���õ�ҩ���ٷֱ�*/
void Brawler::setAmmoBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getAmmoBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ammoBar.png"),
		Rect(0, 0, _ammoBarSize.width * percent, _ammoBarSize.height)));
}

/*�����������ٷֱ�*/
void Brawler::setEnergeBarPercent(float percent)
{
	if (percent < 0)
		percent = 0;
	getEnergyBar()->setSpriteFrame(SpriteFrame::createWithTexture(Director::getInstance()->getTextureCache()->addImage("energyBar.png"),
		Rect(0, 0, _energyBarSize.width * percent, _energyBarSize.height)));
}

/*��ȡӢ�۳���*/
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