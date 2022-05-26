#include "Utils/SceneUtils.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Scene/SelectMap.h"
#include "Scene/SelectBrawler.h"
#include "Scene/GameScene.h"

/*�˵���Ϣ��̬��������ʼ��*/
SceneUtils::AllMap SceneUtils::_map = SceneUtils::MapA;
SceneUtils::AllBrawler SceneUtils::_brawler = SceneUtils::Shelly;

/*ʣ��Ӣ��������̬��������ʼ��Ϊ10*/
INT32 SceneUtils::_brawlerNumber = 10;

/*���õ�problemLoading����������ظ�*/
void SceneUtils::problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

/*�л�����ʱʹ�ã�����Ϊ�ö�����ö����*/
void SceneUtils::changeScene(AllScenes targetScene)
{
	Scene* scene = nullptr;

	/*���ݲ����½�����*/
	switch (targetScene)
	{
		case OpeningAnimation:
			scene = OpeningAnimation::createScene();
			break;
		case GameMenu:
			scene = GameMenu::createScene();
			break;
		case SelectMap:
			scene = SelectMap::createScene();
			break;
		case SelectBrawler:
			scene = SelectBrawler::createScene();
			break;
		case GameScene:
			scene = GameScene::createScene();
			break;
		default:
			break;
	}

	/*�½�ʧ��*/
	if (!scene)
	{
		return;
	}

	/*�½��ɹ���ͨ������������������ʼ���������л�����*/
	Director* director = Director::getInstance();
	if (!director->getRunningScene())
	{
		director->runWithScene(scene);
	}
	else
	{
		director->replaceScene(scene);
	}
}

/*�����*/
void SceneUtils::addLayer(AllLayers targetLayer, Scene* currentScene)
{
	Layer* layer = nullptr;

	/*�½���*/
	switch (targetLayer)
	{
	case Settings:
		layer = Settings::create();
	case Instruction:
		layer = Instruction::create();
	default:
		break;
	}

	/*�½�ʧ��*/
	if (!layer)
	{
		return;
	}

	/*�½��ɹ�����ǰ������Ӳ�*/
	currentScene->addChild(layer);
	
}

/*���ñ���ͼ�����г����๲��*/
void SceneUtils::setBGimage(const char* filename, Layer* layer)
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�ӻ����м��ر���ͼƬ,��������������*/
	auto background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage(filename));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);

	if (background == nullptr)
	{
		SceneUtils::problemLoading(filename);
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		layer->addChild(background, 0);
	}
}