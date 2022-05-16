#ifndef __SELECTMAP_H_
#define __SELECTMAP_H_

#include "cocos2d.h"

/*【行动指示】选择地图界面
和Menu界面类似，基本已经完成
需要完善的细节：
init里面资源路径、xy坐标值、三个回调函数中create()参数的类型和值（向下一场景传递信息）
*/

class SelectMap : public cocos2d::Scene
{
public:
	/*创建场景和初始化*/

	static cocos2d::Scene* createScene();
	virtual bool init();

	/*选择地图 回调函数*/
	void menuMapACallback(cocos2d::Ref* pSender);   //地图A
	void menuMapBCallback(cocos2d::Ref* pSender);   //地图B
	void menuMapCCallback(cocos2d::Ref* pSender);   //地图C

	/*返回 回调函数*/
	void menuBackCallback(cocos2d::Ref* pSender);

	/*自动生成create()的宏*/
	CREATE_FUNC(SelectMap);
};

#endif //__SELECTMAP_H_