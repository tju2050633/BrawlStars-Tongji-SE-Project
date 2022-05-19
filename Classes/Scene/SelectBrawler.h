#ifndef __SELECTBRAWLER_H_
#define __SELECTBRAWLER_H_

#include "cocos2d.h"
#include "SceneManager.h"

/*【行动指示】选择英雄界面
类似，基本完成，完善几个细节：
资源路径、xy坐标值、向下一场景传递的参数类型和值（四个回调函数中createScene()）
*/

USING_NS_CC;
using namespace std;

class SelectBrawler : public Scene
{
private:
	string _map;   //地图A、B、C，暂定

	/*给init使用的初始化函数*/
	void initMenu();	//初始化菜单

	/*选择英雄 回调函数*/
	void menuShellyCallback(Ref* pSender); //雪莉
	void menuPrimoCallback(Ref* pSender);  //普里莫
	void menuNitaCallback(Ref* pSender);   //妮塔
	void menuStuCallback(Ref* pSender);    //斯图

	/*返回 回调函数*/
	void menuBackCallback(Ref* pSender);

public:
	/*创建场景和初始化*/
	static Scene* createScene(SceneManager::AllMap map);/*暂时用的char表示三张地图，后面改*/
	virtual bool init(SceneManager::AllMap map);

	/*自定义create()*/
	static SelectBrawler* create(SceneManager::AllMap map);
};

#endif // !__SELECTBRAWLER_H_