#include "cocos2d.h"
#include "GameMenu.h"
#include "SelectMap.h"
#include "Settings.h"
#include "Instruction.h"

USING_NS_CC;

/*��ó������� ��*/
Scene* GameMenu::createScene()
{
	return GameMenu::create();
}

/*���������� ��*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

/*�˵� ������ʼ�� ��*/
bool GameMenu::init()
{
	/*��ʼ������*/
	if (!Scene::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
		//audio->playBackgroundMusic("�˵���������", true);
	//}

	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*����ģʽ �˵�ѡ��*/
	MenuItemImage* singlePlayerButton = MenuItemImage::create(
		"SingleMode-Normal.png",
		"SingleMode-Active.png",
		CC_CALLBACK_1(GameMenu::menuSinglePlayerCallback, this)
	);
	if (singlePlayerButton == nullptr ||
		singlePlayerButton->getContentSize().width <= 0 ||
		singlePlayerButton->getContentSize().height <= 0)
	{
		problemLoading("'����ģʽ��ť'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*����ģʽ��ťyֵ �ݶ�*/
		singlePlayerButton->setPosition(Vec2(x, y));
	}

	/*����ģʽ �˵�ѡ��*/
	MenuItemImage* multiPlayerButton = MenuItemImage::create(
		"TeamMode-Active.png",
		"TeamMode-Normal.png",
		CC_CALLBACK_1(GameMenu::menuMultiPlayerCallback, this)
	);
	if (multiPlayerButton == nullptr ||
		multiPlayerButton->getContentSize().width <= 0 ||
		multiPlayerButton->getContentSize().height <= 0)
	{
		problemLoading("'����ģʽ��ť'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*����ģʽ��ťyֵ �ݶ�*/
		multiPlayerButton->setPosition(Vec2(x, y));
	}

	/*���� �˵�ѡ��*/
	MenuItemImage* settingsButton = MenuItemImage::create(
		"Btn_setting.png",
		"Btn_setting_PressDown.png",
		CC_CALLBACK_1(GameMenu::menuSettingsCallback, this)
	);
	if (settingsButton == nullptr ||
		settingsButton->getContentSize().width <= 0 ||
		settingsButton->getContentSize().height <= 0)
	{
		problemLoading("'���ð�ť'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*���ð�ťyֵ �ݶ�*/
		settingsButton->setPosition(Vec2(x, y));
	}

	/*��Ϸ˵�� �˵�ѡ��*/
	MenuItemImage* instructionButton = MenuItemImage::create(
		"Book_setting.png",
		"Book_settingActive.png",
		CC_CALLBACK_1(GameMenu::menuInstructionCallback, this)
	);
	if (instructionButton == nullptr ||
		instructionButton->getContentSize().width <= 0 ||
		instructionButton->getContentSize().height <= 0)
	{
		problemLoading("'��Ϸ˵����ť'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*��Ϸ˵����ťyֵ �ݶ�*/
		instructionButton->setPosition(Vec2(x, y));
	}

	/*�˳���Ϸ �˵�ѡ��*/
	MenuItemImage* quitButton = MenuItemImage::create(
		"Exit-Normal.png",
		"Exit-Active.png",
		CC_CALLBACK_1(GameMenu::menuQuitCallback, this)
	);
	if (quitButton == nullptr ||
		quitButton->getContentSize().width <= 0 ||
		quitButton->getContentSize().height <= 0)
	{
		problemLoading("'�˳���Ϸ��ť'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*�˳���Ϸ��ťyֵ �ݶ�*/
		quitButton->setPosition(Vec2(x, y));
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::create(singlePlayerButton, multiPlayerButton, settingsButton, instructionButton, quitButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/*����*/
	auto background = Sprite::create("�˵����汳��ͼƬ");
	if (background == nullptr)
	{
		problemLoading("'�˵����汳��ͼƬ'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}

	return true;
}

/*�˵� ����ģʽ�ص����� ��*/
//������Menu�л���SelectMap
void GameMenu::menuSinglePlayerCallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = SelectMap::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*�˵� ����ģʽ�ص����� ��*/
void GameMenu::menuMultiPlayerCallback(cocos2d::Ref* pSender)
{
	/*��ʱ��ʵ������ģʽ*/
}

/*�˵� ���ûص����� ��*/
//������Menu�л���Settings
void GameMenu::menuSettingsCallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = Settings::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*�˵� ��Ϸ˵���ص����� ��*/
//������Menu�л���Instruction
void GameMenu::menuInstructionCallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = Instruction::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*�˵� �˳���Ϸ�ص����� ��*/
void GameMenu::menuQuitCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}