#ifndef __ROOM_H_
#define __ROOM_H_

#include "cocos2d.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;

class Room : public Layer
{
private:
	/*菜单初始化*/
	void initMenu();

	/*标签初始化*/
	void initLabel();

	/*添加英雄头像*/
	void addPortrait(SceneUtils::AllBrawler brawler);

	Vector<Label*> _labels;

	/*开始 回调函数*/
	void menuStartCallback(Ref* pSender);

	/*添加Shelly 回调函数*/
	void menuAddShellyCallback(Ref* pSender);

	/*添加Nita 回调函数*/
	void menuAddNitaCallback(Ref* pSender);

	/*添加Primo 回调函数*/
	void menuAddPrimoCallback(Ref* pSender);

	/*添加Stu 回调函数*/
	void menuAddStuCallback(Ref* pSender);

	/*返回 回调函数*/
	void menuBackCallback(Ref* pSender);

public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Room);
};

#endif // !__ROOM_H_