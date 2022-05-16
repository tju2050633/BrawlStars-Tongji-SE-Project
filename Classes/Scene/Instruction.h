#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "cocos2d.h"

class Instruction : public cocos2d::Scene 
{
public:
	/*创建场景和初始化*/
	static cocos2d::Scene* createScene();
	virtual bool init();

	/*按键回调函数*/

	/*自动生成create()的宏*/
	CREATE_FUNC(Instruction);
};


#endif // __INSTRUCTION_H_