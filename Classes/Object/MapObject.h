#ifndef __MAPOBJECT_H_
#define __MAPOBJECT_H_

#include "cocos2dx.h"
#include "Unit.h"

USING_NS_CC;

class MapObject : public Unit {
public:
    void attack();  //¹¥»÷£¬²»ÊµÏÖ
};

#endif// !__MAPOBJECT_H_