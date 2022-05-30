#ifndef __SELECT_BRAWLER_H_
#define __SELECT_BRAWLER_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SelectBrawler : public Layer
{
private:
	/*给init使用的初始化函数*/
	void initMenu(); //初始化菜单

	/*选择英雄 回调函数*/
	void menuShellyCallback(Ref* pSender); //雪莉
	void menuPrimoCallback(Ref* pSender);  //普里莫
	void menuNitaCallback(Ref* pSender);   //妮塔
	void menuStuCallback(Ref* pSender);	   //斯图

	/*返回 回调函数*/
	void menuBackCallback(Ref* pSender);

public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectBrawler);
};

#endif // !__SELECT_BRAWLER_H_