#include "cocos2d.h"
#include "Room.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;

Scene* Room::createScene()
{
	auto scene = Scene::create();
	auto layer = Room::create();
	scene->addChild(layer);
	return scene;
}

/*选英雄菜单场景初始化 ×*/
bool Room::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	/*背景*/
	SceneUtils::setBGimage("BGimage/beijing.png", this, SceneUtils::setBGimageWith::TextureCache);



	return true;
}