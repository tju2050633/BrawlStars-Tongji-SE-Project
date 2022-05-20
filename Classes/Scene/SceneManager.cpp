#include "Scene/SceneManager.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Scene/SelectMap.h"
#include "Scene/SelectBrawler.h"
#include "Scene/GameScene.h"

/*单例对象指针初始化为nullptr*/
SceneManager *SceneManager::_sceneManager = nullptr;

/*菜单信息静态变量，初始化*/
SceneManager::AllMap SceneManager::map = SceneManager::MapA;
SceneManager::AllBrawler SceneManager::brawler = SceneManager::Shelly;

/*剩余英雄数量静态变量，初始化为10*/
INT32 SceneManager::brawler_number = 10;

/*获取单例类对象指针*/
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

/*本类不需要初始化，总是返回true*/
bool SceneManager::init()
{
	return true;
}

/*共用的problemLoading，避免代码重复*/
void SceneManager::problemLoading(const char *filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

/*切换场景时使用，参数为该对象内枚举数*/
void SceneManager::changeScene(AllScenes targetScene)
{
	Scene *scene = nullptr;

	/*根据参数新建场景*/
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

	/*新建失败*/
	if (!scene)
	{
		return;
	}

	/*新建成功，通过导演启动场景（初始场景）或切换场景*/
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

/*放置背景图，所有场景类共用*/
void SceneManager::setBGimage(const char *filename, Scene *scene)
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*从缓存中加载背景图片,设置填充可视区域*/
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