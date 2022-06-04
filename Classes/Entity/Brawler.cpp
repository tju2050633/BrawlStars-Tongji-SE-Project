#include <cmath>
#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Utils/SceneUtils.h"

bool Brawler::init()
{
	_ammo = 3;
	_energy = 0;
	_moveSpeedX = 0;
	_moveSpeedY = 0;

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
	for (auto bullet : _bulletVector)
	{
		float angle = bullet->getAngle();					//�ӵ��Ƕ�
		float dx = (bullet->getSpeed() * cos(angle) - _moveSpeedX) * dt;	//�ӵ�ÿ֡�ƶ���
		float dy = (bullet->getSpeed() * sin(angle) - _moveSpeedY) * dt;
		
		bullet->setPosition(bullet->getPosition() + Vec2(dx, dy));
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
void Brawler::takeDamage(INT32 damage)
{
	/*���ø��ຯ��*/
	Entity::takeDamage(damage);

	/*���ûָ�״̬*/
	resetReadyForHeal();
}

/*����*/
void Brawler::die()
{
	/*Ӣ����-1�����GameScene��updateˢ��Label���ݺͳ���Ȧ����BGM���ж�ʤ����*/
	SceneUtils::_brawlerNumber--;
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
		_playerController->getAbilityRoundSprite()->setVisible(true);//
		_playerController->getAbilityCenterSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AbilityCenter.png"));//
		_playerController->getAbilityCenterSprite()->setPosition(_playerController->getAbilityCenterSprite()->getPosition() + Vec2(45, 85));//
	}
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
	_currentHealthPoint += 400;
	setHpBarPercent(float(_currentHealthPoint) / _healthPoint);

	/*���˺�*/
	_attackDamage *= 1.1;
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