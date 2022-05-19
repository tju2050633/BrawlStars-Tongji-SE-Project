#include "cocos2d.h"
#include "Scene/GameScene.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*获得场景对象 √*/
//init需接受参数，不能用CREATE_FUNC自动生成的create()
//用以下模板（仅需改init内参数，效果和create()一样）
Scene* GameScene::createScene(SceneManager::AllMap map, SceneManager::AllBrawler brawler)
{
	auto scene = Scene::create();
	auto layer = GameScene::create( map, brawler);
	scene->addChild(layer);
	return scene;
}

/*自定义create()*/
GameScene* GameScene::create(SceneManager::AllMap map, SceneManager::AllBrawler brawler)
{
	auto scene = new(std::nothrow)GameScene;
	if (scene && scene->init(map, brawler))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

/*错误处理函数 √*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

/*游戏主场景初始化 ×*/
bool GameScene::init(SceneManager::AllMap map, SceneManager::AllBrawler brawler)
{
	/*初始化父类*/
	if (!Scene::init())
	{
		return false;
	}

	/*初始化本类成员变量*/
	m_map = map;
	m_brawler = brawler;

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
		//audio->playBackgroundMusic("选择地图背景音乐", true);
	//}

	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*返回按钮*/
	MenuItemImage* backButton = MenuItemImage::create(
		"button/Back-Normal.png",
		"button/Back-Active.png",
		CC_CALLBACK_1(GameScene::menuBackCallback, this)
	);
	if (backButton == nullptr ||
		backButton->getContentSize().width <= 0 ||
		backButton->getContentSize().height <= 0)
	{
		problemLoading("'返回按钮'");
	}
	else
	{
		float x = visibleSize.width / 2;	/*返回按钮x值，暂定*/
		float y = visibleSize.height / 2;	/*返回按钮x值，暂定*/
		backButton->setPosition(Vec2(x, y));
	}

	/*总的菜单，包含以上菜单选项*/
	Menu* gameScene = Menu::create(backButton, NULL);
	gameScene->setPosition(Vec2::ZERO);
	this->addChild(gameScene, 1);

	/*背景*/
	SceneManager::setBGimage("BGimage1.png", this);

	return true;
}

/*菜单 返回回调函数 √*/
//场景从GameScene切换至SelectBrawler（参数为m_map）
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::GameMenu);
}