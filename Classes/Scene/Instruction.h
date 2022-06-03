#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "cocos2d.h"

USING_NS_CC;

class Instruction : public Layer
{
public:
	/*创建场景和初始化*/
	virtual bool init();
	static Scene* createScene();

	/*自动生成create()的宏*/
	CREATE_FUNC(Instruction);
};

#endif // !__INSTRUCTION_H_