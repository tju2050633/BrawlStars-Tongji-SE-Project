#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class ConstrollerListener;
class Controller :Node {
	/*监听对象*/
	CC_SYNTHESIZE(ConstrollerListener*, _constrollerListener, ConstrollerListener);
	/*精灵图标*/
	CC_SYNTHESIZE(Sprite*, _sprite, Sprite);

};

#endif // !__CONTROLLER_H_
