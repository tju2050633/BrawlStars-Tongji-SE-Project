#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "cocos2d.h"

USING_NS_CC;

class Instruction : public Layer 
{
public:
	/*���������ͳ�ʼ��*/
	virtual bool init();

	/*�����ص�����*/

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(Instruction);
};

#endif // !__INSTRUCTION_H_