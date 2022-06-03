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

	/*新建失败*/
	if (!scene)
	{
		return;
	}
	/*新建成功，通过导演启动场景（初始场景）或切换场景*/
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

/*加载背景图*/
void SceneUtils::setBGimage(const char* filename, Layer* layer, setBGimageWith loadWay)
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。
	
	Sprite* background;
	/*从TextureCache中加载背景图片*/
	if (loadWay == SceneUtils::setBGimageWith::TextureCache)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(filename,
			[](Ref* pSender)
			{
				/*每次成功加载一个纹理 就可以在这里回调方法里设置进度条的进度了 所有纹理加载完成 就跳转界面*/
			});
		background = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage(filename));
	}
	/*从SpriteFrameCache中加载背景图片*/
	else if (loadWay == SceneUtils::setBGimageWith::SpriteFrameCache)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BGimage/BGimage.plist");
		background = Sprite::createWithSpriteFrameName(filename);
	}

	/*设置背景图片填充屏幕*/
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);

	/*加载成功，放置背景图片*/
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
