#ifndef __SELECTMAP_H_
#define __SELECTMAP_H_

#include "cocos2d.h"

/*【行动指示】选择地图界面
和Menu界面类似，基本已经完成
需要完善的细节：
init里面资源路径、xy坐标值、三个回调函数中create()参数的类型和值（向下一场景传递信息）
*/

USING_NS_CC;

class SelectMap : public Scene
{
private:
	/*给init使用的初始化函数*/
	void initMenu();	//初始化菜单
	void initBG();		//初始化背景

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

	/*自动生成create()的宏*/
	CREATE_FUNC(SelectMap);
};

#endif // !__SELECTMAP_H_