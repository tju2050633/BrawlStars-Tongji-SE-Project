#ifndef __AI_H_
#define __AI_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"

USING_NS_CC;

class AI : public Node {
	CC_SYNTHESIZE(Brawler*, _brawler, Brawler); //���ݵ�Ӣ��

public:
	/*��������*/
	CREATE_FUNC(AI);
	virtual bool init();
};

#endif // !__AI_H_
