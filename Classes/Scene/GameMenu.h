#ifndef __MENU_H_
#define __MENU_H_

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

/*【行动指示】菜单界面
这部分主要实现init函数，那几个回调函数只是切换场景而已，基本不用太管
init部分也写的差不多了，还剩素材路径、坐标y值两个细节，都用中文标出来了
还有音频，需要单独一位同学负责一下，SimpleAudioEngine似乎是cocos引擎音频的一部分
*/

USING_NS_CC;

class GameMenu : public Layer
{
private:
	/*给init使用的初始化函数*/
	void initMenu(); //初始化菜单
	void initTrophy(); //初始化奖杯标签

	/*按键回调函数*/
	void menuSinglePlayerCallback(Ref *pSender); //单人模式
	void menuMultiPlayerCallback(Ref *pSender);	 //多人模式
	void menuSettingsCallback(Ref *pSender);	 //游戏设置
	void menuInstructionCallback(Ref *pSender);	 //游戏说明
	void menuQuitCallback(Ref *pSender);		 //退出游戏

public:
	/*创建场景和初始化*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameMenu);
};

#endif // !__MENU_H_