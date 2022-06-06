#include "Entity/Box.h"
#include "Constant/Const.h"
#include "Scene/GameScene.h"

/*初始化*/
bool Box::init()
{
	//属性初始化
	_currentHealthPoint = _healthPoint = BOX_HP;
	_attackDamage = 0;
	_moveSpeed = 0;
	_attackInterval = 0;

	//添加进GameScene的数组
	GameScene::getGameScene()->pushBackEntity(this);

	return true;
}

/*被打碎，掉落buff*/
void Box::die()
{
	/*掉落buff*/
	auto buff = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Buff.png"));
	buff->setPosition(getPosition());
	getParent()->addChild(buff, 1);
	GameScene::getGameScene()->pushBackBuff(buff);

	/*障碍物层移除*/
	Point tileCoord = GameScene::getGameScene()->tileCoordForPosition(getPosition()); //通过指定坐标对应tile坐标
	GameScene::getGameScene()->getCollidable()->removeTileAt(tileCoord);

	/*调用父类die：从场景中移除自身*/
	Entity::die();
}