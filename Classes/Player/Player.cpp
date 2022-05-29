#include "Player/Player.h"
#include "Scene/GameScene.h"

bool Player::init()
{
	setMoveSpeedX(0);
	setMoveSpeedY(0);

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
	setMoveSpeedX(speedX);
}
void Player::setTargetMoveSpeedY(int speedY)
{
	setMoveSpeedY(speedY);
}
INT32 Player::getTargetMoveSpeedX()
{
	return _moveSpeedX;
}
INT32 Player::getTargetMoveSpeedY()
{
	return _moveSpeedY;
}
Brawler* Player::getTargetBrawler()
{
	return _brawler;
}