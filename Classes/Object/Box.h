#ifndef __BOX_H_
#define __BOX_H_

#include "cocos2d.h"
#include "Object/Unit.h"

USING_NS_CC;

class Box : public Unit {
public:
    virtual void die();  //����������buff
};

#endif// !__BOX_H_