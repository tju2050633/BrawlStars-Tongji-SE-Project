#include "Entity/Box.h"
#include "Constant/Const.h"
#include "Scene/GameScene.h"

/*��ʼ��*/
bool Box::init()
{
	//���Գ�ʼ��
	_currentHealthPoint = _healthPoint = BOX_HP;
	_attackDamage = 0;
	_moveSpeed = 0;
	_attackInterval = 0;

	//��ӽ�GameScene������
	GameScene::getGameScene()->pushBackEntity(this);

	return true;
}

/*�����飬����buff*/
void Box::die()
{
	/*����buff*/
	auto buff = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Buff.png"));
	buff->setPosition(getPosition());
	getParent()->addChild(buff, 1);
	GameScene::getGameScene()->pushBackBuff(buff);

	/*�ϰ�����Ƴ�*/
	Point tileCoord = GameScene::getGameScene()->tileCoordForPosition(getPosition()); //ͨ��ָ�������Ӧtile����
	GameScene::getGameScene()->getCollidable()->removeTileAt(tileCoord);

	/*���ø���die���ӳ������Ƴ�����*/
	Entity::die();
}