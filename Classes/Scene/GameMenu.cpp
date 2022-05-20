#include <vector>
#include <string>
#include "cocos2d.h"
#include "Scene/GameMenu.h"
#include "Scene/SceneManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

/*获得场景对象 √*/
Scene *GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
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
	if (!audio->isBackgroundMusicPlaying())
	{
		audio->playBackgroundMusic("菜单背景音乐", true);
	}

	/*菜单*/
	initMenu();

	/*背景*/
	SceneManager::setBGimage("BGimage1.png", this);

	return true;
}

/*菜单 初始化菜单*/
void GameMenu::initMenu()
{
	/*获取visibleSize和origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem *> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = {"SinglePlayer", "MultiPlayer", "Settings", "Instruction", "Quit"};
	//按钮回调函数
	vector<void (GameMenu::*)(Ref * pSender)> CallbackVector = {&GameMenu::menuSinglePlayerCallback,
																&GameMenu::menuMultiPlayerCallback, &GameMenu::menuSettingsCallback,
																&GameMenu::menuInstructionCallback, &GameMenu::menuQuitCallback};
	//按钮尺寸
	vector<float> ScaleVector = {1, 1, 1, 1, 0.2};
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(0.5, 0.5),
		Vec2(0.5, 0.5),
		Vec2(1, 1),
		Vec2(1, 1),
		Vec2(1, 0),
	};
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150),
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y),
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 100),
		Vec2(visibleSize.width + origin.x, origin.y),
	};
	/*逐个设置坐标，存入Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItem *button = MenuItemImage::create(
			StringUtils::format("button/%s-Normal.png", stringVector[i]),
			StringUtils::format("button/%s-Active.png", stringVector[i]),
			bind(CallbackVector[i], this, std::placeholders::_1));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneManager::problemLoading(stringVector[i]);
		else
		{
			button->setScale(ScaleVector[i]);
			button->setAnchorPoint(AnchorVector[i]);
			button->setPosition(PositionVector[i]);
		}
		MenuItemVector.pushBack(button);
	}

	/*总的菜单，包含以上菜单选项*/
	Menu *menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*菜单 单人模式回调函数 切换至SelectMap*/
void GameMenu::menuSinglePlayerCallback(cocos2d::Ref *pSender)
{
	SceneManager::changeScene(SceneManager::SelectMap);
}

/*菜单 多人模式回调函数 */
void GameMenu::menuMultiPlayerCallback(cocos2d::Ref *pSender)
{
	/*暂时不实现联机模式*/
}

/*菜单 设置回调函数 切换至Settings*/
void GameMenu::menuSettingsCallback(cocos2d::Ref *pSender)
{
	SceneManager::changeScene(SceneManager::Settings);
}

/*菜单 游戏说明回调函数 切换至Instruction*/
void GameMenu::menuInstructionCallback(cocos2d::Ref *pSender)
{
	SceneManager::changeScene(SceneManager::Instruction);
}

/*菜单 退出游戏回调函数 √*/
void GameMenu::menuQuitCallback(cocos2d::Ref *pSender)
{
	Director::getInstance()->end();
}