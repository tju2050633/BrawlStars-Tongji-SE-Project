#ifndef __MSG_TYPE_H_
#define __MSG_TYPE_H_

enum MsgType
{
	MsgAttack,
	MsgFoundEnergyBox
};

static std::string  MsgTypes[2] = { "MsgAttack","MsgFoundEnergyBox" };

#endif 	//__MSG_TYPE_H_