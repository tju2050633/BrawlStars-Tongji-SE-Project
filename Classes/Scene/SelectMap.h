#ifndef __SELECT_MAP_H_
#define __SELECT_MAP_H_

#include "cocos2d.h"

USING_NS_CC;

class SelectMap : public Layer
{
private:
	/*给init使用的初始化函数*/
	void initMenu();	//初始化菜单

	/*选择地图 回调函数*/
	void menuMapACallback(Ref* pSender);   //地图A
	void menuMapBCallback(Ref* pSender);   //地图B
	void menuMapCCallback(Ref* pSender);   //地图C

	/*返回 回调函数*/
	void menuBackCallback(Ref* pSender);

public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectMap);
};

#endif // !__SELECT_MAP_H_