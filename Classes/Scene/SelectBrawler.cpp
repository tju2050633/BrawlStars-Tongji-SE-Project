#include "cocos2d.h"
#include "SelectBrawler.h"
#include "GameScene.h"
#include "SelectMap.h"

USING_NS_CC;

/*��ó������� ��*/
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* SelectBrawler::createScene(char map)
{
	auto scene = new(std::nothrow)SelectBrawler;
	if (scene && scene->init(char map))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

/*�������� ��*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

/*ѡӢ�۲˵�������ʼ�� ��*/
bool SelectBrawler::init(char map)
{
	/*��ʼ������*/
	if (!Scene::init())
	{
		return false;
	}

    /*��ʼ�������Ա����*/
    m_map = map;

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("ѡ���ͼ��������", true);
	}

	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*ѩ��*/
	MenuItemImage *ShellyButton = MenuItemImage::create(
		"ѩ��-Normal.png",
		"ѩ��-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuShellyCallback, this)
	);
	if (ShellyButton == nullptr ||
		ShellyButton->getContentSize().width <= 0 ||
		ShellyButton->getContentSize().height <= 0)
	{
		problemLoading("'ѩ��'");
	}
	else
	{
		float x = /*ѩ�� xֵ*/;
		float y = /*ѩ�� yֵ*/;
		ShellyButton->setPosition(Vec2(x, y));
	}

    /*����Ī*/
	MenuItemImage *PrimoButton = MenuItemImage::create(
		"����Ī-Normal.png",
		"����Ī-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuPrimoCallback, this)
	);
	if (PrimoButton == nullptr ||
		PrimoButton->getContentSize().width <= 0 ||
		PrimoButton->getContentSize().height <= 0)
	{
		problemLoading("'����Ī'");
	}
	else
	{
		float x = /*����Ī xֵ*/;
		float y = /*����Ī yֵ*/;
		PrimoButton->setPosition(Vec2(x, y));
	}

    /*����*/
	MenuItemImage *NitaButton = MenuItemImage::create(
		"����-Normal.png",
		"����-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuNitaCallback, this)
	);
	if (NitaButton == nullptr ||
		NitaButton->getContentSize().width <= 0 ||
		NitaButton->getContentSize().height <= 0)
	{
		problemLoading("'����'");
	}
	else
	{
		float x = /*���� xֵ*/;
		float y = /*���� yֵ*/;
		NitaButton->setPosition(Vec2(x, y));
	}

    /*˹ͼ*/
	MenuItemImage *StuButton = MenuItemImage::create(
		"˹ͼ-Normal.png",
		"˹ͼ-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuSituCallback, this)
	);
	if (StuButton == nullptr ||
		StuButton->getContentSize().width <= 0 ||
		StuButton->getContentSize().height <= 0)
	{
		problemLoading("'˹ͼ'");
	}
	else
	{
		float x = /*˹ͼ xֵ*/;
		float y = /*˹ͼ yֵ*/;
		StuButton->setPosition(Vec2(x, y));
	}

    /*���ذ�ť*/
	MenuItemImage *backButton = MenuItemImage::create(
		"���ذ�ť-Normal.png",
		"���ذ�ť-Active.png",
		CC_CALLBACK_1(SelectBrawler::menuBackCallback, this)
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
	Menu* selectMap = Menu::create(ShellyButton, PrimoButton, NitaButton, StuButton, backButton, NULL);
	selectMap->setPosition(Vec2::ZERO);
	this->addChild(selectMap, 1);

	/*����*/
	auto background = Sprite::create("ѡ��Ӣ�۱���ͼƬ");
	if (background == nullptr)
	{
		problemLoading("'ѡ��Ӣ�۱���ͼƬ'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}

	return true;
}

/*ѡ��Ӣ�� ѩ��ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Shelly"��
void SelectBrawler::menuShellyCallback(cocos2d::Ref* pSender)
{
    /*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = GameScene::create(m_map,"Shelly");    //��Ҫ����һ�������ݲ�������ʾѡ��ĵ�ͼ��Ӣ�ۣ�
	Director::getInstance()->replaceScene(          //����������ͺ�ֵ������
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*ѡ��Ӣ�� ����Ī�ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Primo"��
void SelectBrawler::menuPrimoCallback(cocos2d::Ref* pSender)
{
    /*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = GameScene::create(m_map, "Primo");    //��Ҫ����һ�������ݲ�������ʾѡ��ĵ�ͼ��Ӣ�ۣ�
	Director::getInstance()->replaceScene(          //����������ͺ�ֵ������
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*ѡ��Ӣ�� �����ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Nita"��
void SelectBrawler::menuNitaCallback(cocos2d::Ref* pSender)
{
    /*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = GameScene::create(m_map, "Nita");    //��Ҫ����һ�������ݲ�������ʾѡ��ĵ�ͼ��Ӣ�ۣ�
	Director::getInstance()->replaceScene(          //����������ͺ�ֵ������
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*ѡ��Ӣ�� ˹ͼ�ص����� ��*/
//������SelectBrawler�л���GameScene������Ϊm_map, "Situ"��
void SelectBrawler::menuSituCallback(cocos2d::Ref* pSender)
{
    /*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = GameScene::create(m_map, "Situ");    //��Ҫ����һ�������ݲ�������ʾѡ��ĵ�ͼ��Ӣ�ۣ�
	Director::getInstance()->replaceScene(          //����������ͺ�ֵ������
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}

/*�˵� ���ػص����� ��*/
//������SelectBrawler�л���SelectMap
void SelectBrawler::menuBackCallback(cocos2d::Ref* pSender)
{
    /*�л�����������1.����nextScene2.���ݵ���replaceScene*/
	auto nextScene = SelectMap::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));

	MenuItem *item = (MenuItem*)pSender;
}