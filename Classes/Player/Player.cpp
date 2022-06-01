#include "Player/Player.h"
#include "Scene/GameScene.h"

bool Player::init()
{
	return true;
}

/*实现ControllerListener接口*/
void Player::setTargetPosition(Vec2 position)
{
	setPosition(position);
}
Vec2 Player::getTargetPosition()
{
	return getPosition();
}
void Player::setTargetMoveSpeedX(int speedX)
{
	_brawler->setMoveSpeedX(speedX);
}
void Player::setTargetMoveSpeedY(int speedY)
{
	_brawler->setMoveSpeedY(speedY);
}
INT32 Player::getTargetMoveSpeedX()
{
	return _brawler->getMoveSpeedX();
}
INT32 Player::getTargetMoveSpeedY()
{
	return _brawler->getMoveSpeedY();
}
Brawler* Player::getTargetBrawler()
{
	return _brawler;
}