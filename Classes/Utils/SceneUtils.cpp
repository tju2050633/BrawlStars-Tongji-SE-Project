#include "Utils/SceneUtils.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Scene/SelectMap.h"
#include "Scene/SelectBrawler.h"
#include "Scene/GameScene.h"
#include "Scene/Room.h"

USING_NS_CC;

SceneUtils::AllMap SceneUtils::_map = SceneUtils::MapA;
SceneUtils::AllBrawler SceneUtils::_brawler = SceneUtils::Shelly;
INT32 SceneUtils::_brawlerNumber = 0;
INT32 SceneUtils::_shellyNumber = 0;
INT32 SceneUtils::_nitaNumber = 0;
INT32 SceneUtils::_primoNumber = 0;
INT32 SceneUtils::_stuNumber = 0;

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
		case Settings:
			scene = Settings::createScene();
			break;
		case Instruction:
			scene = Instruction::createScene();
			break;
		case Room:
			scene = Room::createScene();
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
	TransitionScene* pTransScene = TransitionCrossFade::create(0.5f, scene);
	Director* director = Director::getInstance();
	if (!director->getRunningScene())
	{
		director->runWithScene(pTransScene);
	}
	else
	{
		director->replaceScene(pTransScene);
	}
}

/*���ر���ͼ*/
void SceneUtils::setBGimage(const char* filename, Layer* layer, setBGimageWith loadWay)
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�
	
	Sprite* background;
	/*��TextureCache�м��ر���ͼƬ*/
	if (loadWay == SceneUtils::setBGimageWith::TextureCache)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(filename,
			[](Ref* pSender)
			{
				/*ÿ�γɹ�����һ������ �Ϳ���������ص����������ý������Ľ����� �������������� ����ת����*/
			});
		background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage(filename));
	}
	/*��SpriteFrameCache�м��ر���ͼƬ*/
	else if (loadWay == SceneUtils::setBGimageWith::SpriteFrameCache)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BGimage/BGimage.plist");
		background = Sprite::createWithSpriteFrameName(filename);
	}

	/*���ñ���ͼƬ�����Ļ*/
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);

	/*���سɹ������ñ���ͼƬ*/
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
