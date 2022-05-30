#include "Utils/SceneUtils.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Scene/SelectMap.h"
#include "Scene/SelectBrawler.h"
#include "Scene/GameScene.h"

USING_NS_CC;
/*菜单信息静态变量，初始化*/
SceneUtils::AllMap SceneUtils::_map = SceneUtils::MapA;
SceneUtils::AllBrawler SceneUtils::_brawler = SceneUtils::Shelly;

/*剩余英雄数量静态变量，初始化为10*/
INT32 SceneUtils::_brawlerNumber = 10;

/*共用的problemLoading，避免代码重复*/
void SceneUtils::problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

/*切换场景时使用，参数为该对象内枚举数*/
void SceneUtils::changeScene(AllScenes targetScene)
{
	Scene* scene = nullptr;

	/*根据参数新建场景*/
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
		case Instruction:
			scene = Instruction::createScene();
		default:
			break;
	}

	/*新建失败*/
	if (!scene)
	{
		return;
	}
	/*新建成功，通过导演启动场景（初始场景）或切换场景*/
	TransitionScene* pTransScene = TransitionCrossFade::create(1.0f, scene);
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

/*增添层*/
void SceneUtils::addLayer(AllLayers targetLayer, Scene* currentScene)
{
}

/*放置背景图，所有场景类共用*/
void SceneUtils::setBGimage(const char* filename, Layer* layer)
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//Director::getInstance()->getTextureCache()->addImageAsync("HelloWorld.png", CC_CALLBACK_1(HelloWorld::imageLoadedCallback, this));

	//try
	Director::getInstance()->getTextureCache()->addImageAsync(filename,
		[](Ref* pSender)
		{
			/*每次成功加载一个纹理 就可以在这里回调方法里设置进度条的进度了 所有纹理加载完成 就跳转界面*/
		});

	/*从缓存中加载背景图片,设置填充可视区域*/
	//auto background = Sprite::createWithTexture();
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
//重载设置背景函数，使用SpriteFrameCache
void SceneUtils::setBGimage(const char* filename, Layer* layer, INT32 a) {
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*从缓存中加载背景图片,设置填充可视区域*/

	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("BGimage/BGimage.plist");
	Sprite* background = Sprite::createWithSpriteFrameName(filename);

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