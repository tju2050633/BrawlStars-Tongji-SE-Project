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

/*ѡӢ�۲˵�������ʼ�� ��*/
bool Room::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	/*����*/
	SceneUtils::setBGimage("BGimage/beijing.png", this, SceneUtils::setBGimageWith::TextureCache);



	return true;
}