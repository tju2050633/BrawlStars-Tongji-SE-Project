#include "cocos2d.h"
#include <vector>
#include <string>
#include "Room.h"
#include "Utils/SceneUtils.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

/*��ó������� ��*/
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

	/*��ʼ��������Ϣ����Ӣ������*/
	SceneUtils::_brawlerNumber = 0;
	SceneUtils::_shellyNumber = 0;
	SceneUtils::_nitaNumber = 0;
	SceneUtils::_primoNumber = 0;
	SceneUtils::_stuNumber = 0;
	
	/*�˵�*/
	initMenu();

	/*��ǩ*/
	initLabel();

	/*���Ӣ��ͷ��*/
	addPortrait(SceneUtils::_brawler);	//������ͷ��
	SceneUtils::_brawlerNumber++;

	/*����*/
	SceneUtils::setBGimage("BGimage/Background.png", this, SceneUtils::setBGimageWith::TextureCache);

	return true;
}

/*�˵���ʼ��*/
void Room::initMenu()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "Start", "Shelly", "Primo", "Nita", "Stu", "Back"};
	//��ť�ص�����
	vector<void (Room::*)(Ref* pSender)> CallbackVector = {
		&Room::menuStartCallback,
		& Room::menuAddShellyCallback,
		& Room::menuAddPrimoCallback,
		& Room::menuAddNitaCallback,
		& Room::menuAddStuCallback,
		& Room::menuBackCallback };
	//��ť�ߴ�
	vector<float> ScaleVector = { 1, 0.2, 0.2, 0.2, 0.2, 1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0.5, 0.5), Vec2(0.5, 0.5),
		Vec2(0, 1) };
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 10 + origin.y),
		Vec2(5 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(6.33 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(7.66 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(9 * visibleSize.width / 10 + origin.x, visibleSize.height / 4 + origin.y),
		Vec2(origin.x, visibleSize.height + origin.y) };

	/*���������ť��������Ϣ������Vector*/
	for (ssize_t i = 0; i < stringVector.size(); i++)
	{
		MenuItemImage* button = MenuItemImage::create(
			"Portrait/" + stringVector.at(i) + "-Normal.png",
			"Portrait/" + stringVector.at(i) + "-Active.png",
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

/*��ǩ��ʼ��*/
void Room::initLabel()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	//Label���ı�
	vector<string> stringVector = { "Player", "AI #1", "AI #2", "AI #3", "AI #4", "AI #5","AI #6", "AI #7", "AI #8", "AI #9", "Add AI brawler:" };
	//Label����
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 50),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 130),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 210),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 290),
		Vec2(visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 370),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 50),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 130),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 210),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 290),
		Vec2(2 * visibleSize.width / 3 + origin.x, visibleSize.height + origin.y - 370),
		Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y), };

	/*�������Label*/
	for (ssize_t i = 0; i < stringVector.size(); i++)
	{
		_labels.pushBack(Label::createWithTTF(stringVector.at(i), "fonts/arial.ttf", 48));
		_labels.at(i)->setPosition(PositionVector.at(i));
		this->addChild(_labels.at(i), 1);
	}

	/*AI #1~9������*/
	for (int i = 1; i <= 9; i++)
	{
		_labels.at(i)->setVisible(false);
	}
}

/*���Ӣ��ͷ��*/
void Room::addPortrait(SceneUtils::AllBrawler brawler)
{
	/*��ȡ��ӦӢ��ͼ��*/
	Sprite* portrait;
	switch (brawler)
	{
	case SceneUtils::Shelly:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Shelly-Normal.png"));
		break;
	case SceneUtils::Primo:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Primo-Normal.png"));
		break;
	case SceneUtils::Nita:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Nita-Normal.png"));
		break;
	case SceneUtils::Stu:
		portrait = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Portrait/Stu-Normal.png"));
		break;
	default:
		break;
	}
	portrait->setScale(0.2);

	/*����λ�ã�����ͼ�񣬶�Ӧ��ǩ�ɼ�*/
	INT32 index = SceneUtils::_brawlerNumber;
	portrait->setPosition(_labels.at(index)->getPosition() + Vec2(150, 0));
	_labels.at(index)->setVisible(true);
	
	this->addChild(portrait, 1);
}

/*��ʼ �ص�����*/
void Room::menuStartCallback(Ref* pSender)
{
	if(SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");

	//Ӣ������>=2
	if (SceneUtils::_brawlerNumber == 1)
		return;

	if (SceneUtils::_musicOn)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Combat.mp3", true);
	}
	SceneUtils::changeScene(SceneUtils::GameScene);
}

/*���Shelly �ص�����*/
void Room::menuAddShellyCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Shelly);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_shellyNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*���Nita �ص�����*/
void Room::menuAddNitaCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Nita);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_nitaNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*���Primo �ص�����*/
void Room::menuAddPrimoCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Primo);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_primoNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*���Stu �ص�����*/
void Room::menuAddStuCallback(Ref* pSender)
{
	if (SceneUtils::_brawlerNumber == 10)
		return;
	addPortrait(SceneUtils::Stu);
	SceneUtils::_brawlerNumber++;
	SceneUtils::_stuNumber++;

	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
}

/*����SelectBrawler*/
void Room::menuBackCallback(Ref* pSender)
{
	if (SceneUtils::_effectOn)
		SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SceneUtils::changeScene(SceneUtils::AllScenes::SelectBrawler);
}