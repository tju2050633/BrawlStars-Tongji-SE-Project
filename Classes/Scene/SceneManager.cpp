#include "Scene/SceneManager.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Scene/SelectMap.h"
#include "Scene/SelectBrawler.h"
#include "Scene/GameScene.h"

/*��������ָ���ʼ��Ϊnullptr*/
SceneManager *SceneManager::_sceneManager = nullptr;

/*�˵���Ϣ��̬��������ʼ��*/
SceneManager::AllMap SceneManager::map = SceneManager::MapA;
SceneManager::AllBrawler SceneManager::brawler = SceneManager::Shelly;

/*ʣ��Ӣ��������̬��������ʼ��Ϊ10*/
INT32 SceneManager::brawler_number = 10;

/*��ȡ���������ָ��*/
SceneManager *SceneManager::getInstance()
{
	if (!_sceneManager)
	{
		_sceneManager = new SceneManager();
		if (_sceneManager && _sceneManager->init())
		{
			_sceneManager->autorelease();
			_sceneManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(_sceneManager);
			_sceneManager = nullptr;
		}
	}
	return _sceneManager;
}

/*���಻��Ҫ��ʼ�������Ƿ���true*/
bool SceneManager::init()
{
	return true;
}

/*���õ�problemLoading����������ظ�*/
void SceneManager::problemLoading(const char *filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

/*�л�����ʱʹ�ã�����Ϊ�ö�����ö����*/
void SceneManager::changeScene(AllScenes targetScene)
{
	Scene *scene = nullptr;

	/*���ݲ����½�����*/
	switch (targetScene)
	{
	case OpeningAnimation:
		scene = OpeningAnimation::createScene();
		break;
	case GameMenu:
		scene = GameMenu::createScene();
		break;
	case Settings:
		scene = Settings::createScene();
		break;
	case Instruction:
		scene = Instruction::createScene();
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
	Director *director = Director::getInstance();
	if (!director->getRunningScene())
	{
		director->runWithScene(scene);
	}
	else
	{
		director->replaceScene(scene);
	}
}

/*���ñ���ͼ�����г����๲��*/
void SceneManager::setBGimage(const char *filename, Scene *scene)
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*�ӻ����м��ر���ͼƬ,��������������*/
	auto background = Sprite::createWithTexture(Texture::getInstance()->addImage(filename));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);

	if (background == nullptr)
	{
		SceneManager::problemLoading(filename);
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		scene->addChild(background, 0);
	}
}