#include "cocos2d.h"
#include "SelectMap.h"
#include "SelectBrawler.h"
#include "GameMenu.h"

USING_NS_CC;

/*��ó������� ��*/
Scene* SelectMap::createScene()
{
	return SelectMap::create();
}

/*�������� ��*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

/*ѡģʽ�˵�������ʼ�� ��*/
bool SelectMap::init()
{
	/*��ʼ������*/
	if (!Scene::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("ѡ���ͼ��������", true);
	}

	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*��ͼAѡ��*/
	MenuItemImage* MapAButton = MenuItemImage::create(
		"��ͼA-Normal.png",
		"��ͼA-Active.png",
		CC_CALLBACK_1(SelectMap::menuMapACallback, this)
	);
	if (MapAButton == nullptr ||
		MapAButton->getContentSize().width <= 0 ||
		MapAButton->getContentSize().height <= 0)
	{
		problemLoading("'��ͼA��ť'");
	}
	else
	{
		float x = /*��ͼA xֵ*/;
		float y = /*��ͼA yֵ*/;
		MapAButton->setPosition(Vec2(x, y));
	}

	/*��ͼBѡ��*/
	MenuItemImage* MapBButton = MenuItemImage::create(
		"��ͼB-Normal.png",
		"��ͼB-Active.png",
		CC_CALLBACK_1(SelectMap::menuMapBCallback, this)
	);
	if (MapBButton == nullptr ||
		MapBButton->getContentSize().width <= 0 ||
		MapBButton->getContentSize().height <= 0)
	{
		problemLoading("'��ͼB��ť'");
	}
	else
	{
		float x = /*��ͼB xֵ*/;
		float y = /*��ͼB yֵ*/;
		MapBButton->setPosition(Vec2(x, y));
	}

	/*��ͼCѡ��*/
	MenuItemImage* MapCButton = MenuItemImage::create(
		"��ͼC-Normal.png",
		"��ͼC-Active.png",
		CC_CALLBACK_1(SelectMap::menuMapCCallback, this)
	);
	if (MapCButton == nullptr ||
		MapCButton->getContentSize().width <= 0 ||
		MapCButton->getContentSize().height <= 0)
	{
		problemLoading("'��ͼC��ť'");
	}
	else
	{
		float x = /*��ͼC xֵ*/;
		float y = /*��ͼC yֵ*/;
		MapCButton->setPosition(Vec2(x, y));
	}

	/*���ذ�ť*/
	MenuItemImage* backButton = MenuItemImage::create(
		"���ذ�ť-Normal.png",
		"���ذ�ť-Active.png",
		CC_CALLBACK_1(SelectMap::menuBackCallback, this)
	);
	if (backButton == nullptr ||
		backButton->getContentSize().width <= 0 ||
		backButton->getContentSize().height <= 0)
	{
		problemLoading("'���ذ�ť'");
	}
	else
	{
		float x = /*���ذ�ť xֵ*/;
		float y = /*���ذ�ť yֵ*/;
		backButton->setPosition(Vec2(x, y));
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* selectMap = Menu::create(MapAButton, MapBButton, MapCButton, backButton, NULL);
	selectMap->setPosition(Vec2::ZERO);
	this->addChild(selectMap, 1);

	/*����*/
	auto background = Sprite::create("ѡ���ͼ����ͼƬ");
	if (background == nullptr)
	{
		problemLoading("'ѡ���ͼ����ͼƬ'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}

	return true;
}

/*ѡ���ͼ ��ͼA�ص����� ��*/
//������SelectMap�л���SelectBrawler������Ϊ'A'��
void SelectMap::menuMapACallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = SelectBrawler::create('A');    //��Ҫ����һ�������ݲ�������ʾѡ��ĵ�ͼ��
	Director::getInstance()->replaceScene(          //����������ͺ�ֵ������
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*ѡ���ͼ ��ͼB�ص����� ��*/
//������SelectMap�л���SelectBrawler������Ϊ'B'��
void SelectMap::menuMapBCallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = SelectBrawler::create('B');
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*ѡ���ͼ ��ͼC�ص����� ��*/
//������SelectMap�л���SelectBrawler������Ϊ'C'��
void SelectMap::menuMapCCallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = SelectBrawler::create('C');
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}

/*ѡ���ͼ ���ػص����� ��*/
//������SelectMap�л���Menu
void SelectMap::menuBackCallback(cocos2d::Ref* pSender)
{
	/*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = Menu::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem* item = (MenuItem*)pSender;
}