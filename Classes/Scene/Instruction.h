#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "cocos2d.h"

class Instruction : public cocos2d::Scene 
{
public:
	/*���������ͳ�ʼ��*/
	static cocos2d::Scene* createScene();
	virtual bool init();

	/*�����ص�����*/

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(Instruction);
};


#endif // __INSTRUCTION_H_