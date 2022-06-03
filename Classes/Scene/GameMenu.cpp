#include "cocos2d.h"
#include <string>
#include <fstream>
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Utils/SceneUtils.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;


/*��ó������� ��*/
Scene* GameMenu::createScene()
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

	/*����*/
	

	/*�˵�*/
	initMenu();

	/*����*/
	initTrophy();

	/*����*/
	SceneUtils::setBGimage("BGimage/GameMenu.png", this, SceneUtils::setBGimageWith::TextureCache);

	return true;
}

/*�˵� ��ʼ���˵�*/
void GameMenu::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ����*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "SinglePlayer", "MultiPlayer", "Settings", "Instruction", "Quit" };
	//��ť�ص�����
	vector<void (GameMenu::*)(Ref* pSender)> CallbackVector = { &GameMenu::menuSinglePlayerCallback,
																&GameMenu::menuMultiPlayerCallback, &GameMenu::menuSettingsCallback,
																&GameMenu::menuInstructionCallback, &GameMenu::menuQuitCallback };
	//��ť�ߴ�
	vector<float> ScaleVector = { 1, 1, 1, 1, 0.2 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(1, 1),
		Vec2(1, 1),
		Vec2(1, 0),
	};
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 100),
		Vec2(visibleSize.width + origin.x, origin.y),
	};
	/*����������꣬����Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItem* button = MenuItemImage::create(
			"button/" + stringVector.at(i) + "-Normal.png",
			"button/" + stringVector.at(i) + "-Active.png",
			bind(CallbackVector.at(i), this, std::placeholders::_1));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneUtils::problemLoading(stringVector.at(i).c_str());
		else
		{
			button->setScale(ScaleVector.at(i));
			button->setAnchorPoint(AnchorVector.at(i));
			button->setPosition(PositionVector.at(i));
		}
		MenuItemVector.pushBack(button);
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*�˵� ��ʼ��������ǩ*/
void GameMenu::initTrophy()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*����ͼ��*/
	auto trophy = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("trophy.png"));
	trophy->setAnchorPoint(Vec2(0, 1));
	trophy->setPosition(Vec2(origin.x, visibleSize.height + origin.y + 10));
	trophy->setScale(0.2);
	trophy->setRotation(10);
	this->addChild(trophy, 1);

	/*��������*/
	ifstream in("trophy.txt", ios::in);
	int iTrophy;
	if (in.good())
		in >> iTrophy;
	else
		iTrophy = 0;

	auto label = Label::createWithTTF(StringUtils::format("%d", iTrophy).c_str(), "fonts/Marker Felt.ttf", 48);
	label->setAnchorPoint(Vec2(0, 1));
	label->setPosition(Vec2(origin.x + 130, visibleSize.height + origin.y - 15));
	label->setTextColor(Color4B::YELLOW);
	this->addChild(label, 1);
}

/*�˵� ����ģʽ�ص����� �л���SelectMap*/
void GameMenu::menuSinglePlayerCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::SelectMap);
}

/*�˵� ����ģʽ�ص����� */
void GameMenu::menuMultiPlayerCallback(cocos2d::Ref* pSender)
{
	/*��ʱ��ʵ������ģʽ*/
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*�˵� ���ûص����� �л���Settings*/
void GameMenu::menuSettingsCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::Settings);
}

/*�˵� ��Ϸ˵���ص����� �л���Instruction*/
void GameMenu::menuInstructionCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::Instruction);
}

/*�˵� �˳���Ϸ�ص����� ��*/
void GameMenu::menuQuitCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	Director::getInstance()->end();
}