#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "cocos2d.h"

USING_NS_CC;

class Instruction : public Scene 
{
public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();

	/*按键回调函数*/

	/*自动生成create()的宏*/
	CREATE_FUNC(Instruction);
};

#endif // !__INSTRUCTION_H_