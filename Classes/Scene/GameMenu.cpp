#include "cocos2d.h"
#include "Scene/GameMenu.h"
#include "Scene/SceneUtils.h"

USING_NS_CC;
using namespace std;

/*��ó������� ��*/
Scene *GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

/*�˵� ������ʼ�� ��*/
bool GameMenu::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	// auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	// if (!audio->isBackgroundMusicPlaying())
	// {
	// 	audio->playBackgroundMusic("�˵���������", true);
	// }

	/*�˵�*/
	initMenu();

	/*����*/
	SceneUtils::setBGimage("BGimage/GameMenu.png", this);

	return true;
}

/*�˵� ��ʼ���˵�*/
void GameMenu::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ����*/
	Vector<MenuItem *> MenuItemVector;
	//�ļ������õ��ַ���
	Vector<String> stringVector = {"SinglePlayer", "MultiPlayer", "Settings", "Instruction", "Quit"};
	//��ť�ص�����
	Vector<void (GameMenu::*)(Ref * pSender)> CallbackVector = {&GameMenu::menuSinglePlayerCallback,
																&GameMenu::menuMultiPlayerCallback, &GameMenu::menuSettingsCallback,
																&GameMenu::menuInstructionCallback, &GameMenu::menuQuitCallback};
	//��ť�ߴ�
	Vector<float> ScaleVector = {1, 1, 1, 1, 0.2};
	//��ťê��
	Vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(1, 1),
		Vec2(1, 1),
		Vec2(1, 0),
	};
	//��ť����
	Vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 100),
		Vec2(visibleSize.width + origin.x, origin.y),
	};
	/*����������꣬����Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItem *button = MenuItemImage::create(
			StringUtils::format("button/%s-Normal.png", stringVector.at(i)),
			StringUtils::format("button/%s-Active.png", stringVector.at(i)),
			bind(CallbackVector.at(i), this, std::placeholders::_1));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneUtils::problemLoading(stringVector.at(i));
		else
		{
			button->setScale(ScaleVector.at(i));
			button->setAnchorPoint(AnchorVector.at(i));
			button->setPosition(PositionVector.at(i));
		}
		MenuItemVector.pushBack(button);
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu *menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*�˵� ����ģʽ�ص����� �л���SelectMap*/
void GameMenu::menuSinglePlayerCallback(cocos2d::Ref *pSender)
{
	SceneUtils::changeScene(SceneUtils::SelectMap);
}

/*�˵� ����ģʽ�ص����� */
void GameMenu::menuMultiPlayerCallback(cocos2d::Ref *pSender)
{
	/*��ʱ��ʵ������ģʽ*/
}

/*�˵� ���ûص����� �л���Settings*/
void GameMenu::menuSettingsCallback(cocos2d::Ref *pSender)
{
	addChild(Settings::create());
}

/*�˵� ��Ϸ˵���ص����� �л���Instruction*/
void GameMenu::menuInstructionCallback(cocos2d::Ref *pSender)
{
	addChild(Instruction::create());
}

/*�˵� �˳���Ϸ�ص����� ��*/
void GameMenu::menuQuitCallback(cocos2d::Ref *pSender)
{
	Director::getInstance()->end();
}