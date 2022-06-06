#ifndef __FSMSTATE_H_
#define __FSMSTATE_H_

#include "cocos2d.h"
#include "Entity/Brawler.h"
#include "Player/AI.h"
#include "Utils/MsgType.h"
class AI;
USING_NS_CC;

/* FSM有限状态机
  状态机构成
  1.状态: idle ,attacking ,walking , dead
  2.事件: 满足一定条件则改变状态到指定态
  3.动作: 1.与Player相同的动作
		2.实时获取目标对象的坐标
		3.死后记录排名，销毁自身
*/
/*路线设计方面：
  漫步，遇到其他敌人开始攻击（一定范围内）
  1.不可所有AI以主英雄为目标固定攻击主英雄.
  2.可以固定AI的起始出发点和目标点,在行走途中可能会有能量宝箱和敌人暂停路线，
	五个AI起始位置如下,以主角为目标点，隔段时间监测与主角距离，攻击主角，AIUpdate的时间参数应大于Player
  （有一个AI一开始就可攻击主角，终点为左边中点，此处不考虑是否会增加玩家游戏难度）
  -----------
  |*       *|
  |         |
  |   *     |
  |         |
  |*       *|
  -----------
  四个AI始终攻击各自四个角的AI,图为起始点
  -----------
  |    *    |
  |         |
  |*       *|
  |         |
  |    *    |
  -----------
  3.AI太智能难免增加工作量，可酌情减少AI个数及功能

*/
/*
	说明：
	1.由于不知宝箱情况，暂定AI不会获取宝箱
	2.先完成一个AI实时监测攻击玩家的功能，
	3.所有AI须有检测被攻击的功能，无逃跑功能，不管血量多少均攻击。
	4.由于AI所有动作Player都有，考虑复用代码

*/

class FSMState :public Node {
public:
	virtual void execute(AI* _ai, MsgType _msgType) = 0;
};

#endif // __FSMSTATE_H_