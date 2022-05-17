#include "cocos2d.h"
#include "Scene/GameMenu.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*获得场景对象 √*/
Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

/*错误处理函数 √*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

/*菜单 场景初始化 ×*/
bool GameMenu::init()
{
	/*初始化父类*/
	if (!Scene::init())
	{
		return false;
	}

	/*声音，这个SimpleAudioEngine后期看是加上还是换别的*/
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("菜单背景音乐", true);
	}

	/*菜单*/
	initMenu();

	/*背景*/
	initBG();

	return true;
}

/*菜单 初始化菜单*/
void GameMenu::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*单人模式 菜单选项*/
	MenuItemImage* singlePlayerButton = MenuItemImage::create(
		"button/SingleMode-Normal.png",
		"button/SingleMode-Active.png",
		CC_CALLBACK_1(GameMenu::menuSinglePlayerCallback, this)
	);
	if (singlePlayerButton == nullptr ||
		singlePlayerButton->getContentSize().width <= 0 ||
		singlePlayerButton->getContentSize().height <= 0)
	{
		problemLoading("'单人模式按钮'");
	}
	else
	{
		float x = visibleSize.width / 2 + origin.x;
		float y = visibleSize.height / 2 + origin.y;/*单人模式按钮y值 暂定*/
		singlePlayerButton->setPosition(Vec2(x, y));
	}
	
	/*多人模式 菜单选项*/
	MenuItemImage* multiPlayerButton = MenuItemImage::create(
		"button/TeamMode-Active.png",
		"button/TeamMode-Normal.png",
		CC_CALLBACK_1(GameMenu::menuMultiPlayerCallback, this)
	);
	if (multiPlayerButton == nullptr ||
		multiPlayerButton->getContentSize().width <= 0 ||
		multiPlayerButton->getContentSize().height <= 0)
	{
		problemLoading("'多人模式按钮'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*多人模式按钮y值 暂定*/
		multiPlayerButton->setPosition(Vec2(x, y));
	}

	/*设置 菜单选项*/
	MenuItemImage* settingsButton = MenuItemImage::create(
		"button/Btn_setting.png",
		"button/Btn_setting_PressDown.png",
		CC_CALLBACK_1(GameMenu::menuSettingsCallback, this)
	);
	if (settingsButton == nullptr ||
		settingsButton->getContentSize().width <= 0 ||
		settingsButton->getContentSize().height <= 0)
	{
		problemLoading("'设置按钮'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*设置按钮y值 暂定*/
		settingsButton->setPosition(Vec2(x, y));
	}

	/*游戏说明 菜单选项*/
	MenuItemImage* instructionButton = MenuItemImage::create(
		"button/Book_setting.png",
		"button/Book_settingActive.png",
		CC_CALLBACK_1(GameMenu::menuInstructionCallback, this)
	);
	if (instructionButton == nullptr ||
		instructionButton->getContentSize().width <= 0 ||
		instructionButton->getContentSize().height <= 0)
	{
		problemLoading("'游戏说明按钮'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*游戏说明按钮y值 暂定*/
		instructionButton->setPosition(Vec2(x, y));
	}

	/*退出游戏 菜单选项*/
	MenuItemImage* quitButton = MenuItemImage::create(
		"button/Exit-Normal.png",
		"button/Exit-Active.png",
		CC_CALLBACK_1(GameMenu::menuQuitCallback, this)
	);
	if (quitButton == nullptr ||
		quitButton->getContentSize().width <= 0 ||
		quitButton->getContentSize().height <= 0)
	{
		problemLoading("'退出游戏按钮'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;/*退出游戏按钮y值 暂定*/
		quitButton->setPosition(Vec2(x, y));
	}

	/*总的菜单，包含以上菜单选项*/
	Menu* menu = Menu::create(singlePlayerButton, multiPlayerButton, settingsButton, instructionButton, quitButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*菜单 初始化背景*/
void GameMenu::initBG()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*加载背景图片*/
	auto background = Sprite::create("菜单界面背景图片");
	if (background == nullptr)
	{
		problemLoading("'菜单界面背景图片'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}
}

/*菜单 单人模式回调函数 切换至SelectMap*/
void GameMenu::menuSinglePlayerCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::SelectMap);
}

/*菜单 多人模式回调函数 */
void GameMenu::menuMultiPlayerCallback(cocos2d::Ref* pSender)
{
	/*暂时不实现联机模式*/
}

/*菜单 设置回调函数 切换至Settings*/
void GameMenu::menuSettingsCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::Settings);
}

/*菜单 游戏说明回调函数 切换至Instruction*/
void GameMenu::menuInstructionCallback(cocos2d::Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::Instruction);
}

/*菜单 退出游戏回调函数 √*/
void GameMenu::menuQuitCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}