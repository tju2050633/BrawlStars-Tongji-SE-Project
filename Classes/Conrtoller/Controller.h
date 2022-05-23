#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class ConstrollerListener;
class Controller :Node {
	/*��������*/
	CC_SYNTHESIZE(ConstrollerListener*, _constrollerListener, ConstrollerListener);
	/*����ͼ��*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);

};

#endif // !__CONTROLLER_H_
