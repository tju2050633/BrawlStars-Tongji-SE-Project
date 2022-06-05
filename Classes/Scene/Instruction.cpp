#include "cocos2d.h"
#include "Instruction.h"
#include "GameMenu.h"
#include "Utils/SceneUtils.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*��ó������� ��*/
Scene* Instruction::createScene()
{
	auto scene = Scene::create();
	auto layer = Instruction::create();
	scene->addChild(layer);
	return scene;
}

/*��Ϸ˵�� ������ʼ�� ��*/   //okk
bool Instruction::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*����*/
	SceneUtils::setBGimage("BGimage/Instruction.png", this, SceneUtils::setBGimageWith::TextureCache);

	//�˵�
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//���ذ�ť

	MenuItemImage* button = MenuItemImage::create("button/Back-Normal.png", "button/Back-Active.png",
		[](Ref* pSender)
		{
			if (SceneUtils::_effectOn)
				SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
			SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
		});

	if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
		SceneUtils::problemLoading("button/Back-Normal.png");
	else
	{
		button->setScale(1);
		button->setAnchorPoint(Vec2(0, 1));
		button->setPosition(Vec2(origin.x, visibleSize.height + origin.y));
	}
	menu->addChild(button);

	return true;
}