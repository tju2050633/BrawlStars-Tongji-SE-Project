#ifndef __SELECTBRAWLER_H_
#define __SELECTBRAWLER_H_

#include "cocos2d.h"

/*【行动指示】选择英雄界面
类似，基本完成，完善几个细节：
资源路径、xy坐标值、向下一场景传递的参数类型和值（四个回调函数中createScene()）
*/

class SelectBrawler : public cocos2d::Scene
{
private:
	std::string m_map;   //地图A、B、C，暂定

public:
	/*创建场景和初始化*/
	static cocos2d::Scene* createScene(std::string map);/*暂时用的char表示三张地图，后面改*/
	virtual bool init(std::string map);

	/*选择英雄 回调函数*/
	void menuShellyCallback(cocos2d::Ref* pSender); //雪莉
	void menuPrimoCallback(cocos2d::Ref* pSender);  //普里莫
	void menuNitaCallback(cocos2d::Ref* pSender);   //妮塔
	void menuSituCallback(cocos2d::Ref* pSender);    //斯图

	/*返回 回调函数*/
	void menuBackCallback(cocos2d::Ref* pSender);

	/*自定义create()*/
	static SelectBrawler* create(std::string map);
};

#endif //__SELECTBRAWLER_H_