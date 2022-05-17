#include "Scene/SceneManager.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Scene/SelectMap.h"
#include "Scene/SelectBrawler.h"
#include "Scene/GameScene.h"
#include "Scene/SceneInfo.h"

/*单例对象指针初始化为nullptr*/
SceneManager* SceneManager::_sceneManager = nullptr;

/*菜单信息静态变量，初始化为空*/
string SceneInfo::map = "";
string SceneInfo::brawler = "";


/*获取单例类对象指针*/
SceneManager* SceneManager::getInstance() {
	if (!_sceneManager) {
		_sceneManager = new SceneManager();
		if (_sceneManager && _sceneManager->init()) {
			_sceneManager->autorelease();
			_sceneManager->retain();
		}
		else {
			CC_SAFE_DELETE(_sceneManager);
			_sceneManager = nullptr;
		}
	}
	return _sceneManager;
}

/*本类不需要初始化，总是返回true*/
bool SceneManager::init() {
	return true;
}

/*切换场景时使用，参数为该对象内枚举数*/
void SceneManager::changeScene(AllScenes targetScene) {
	Scene* scene = nullptr;

    /*根据参数新建场景*/
	switch (targetScene) {
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
		scene = SelectBrawler::createScene(SceneInfo::map);
		break;
    case GameScene:
		scene = GameScene::createScene(SceneInfo::map, SceneInfo::brawler);
		break;
    default:
        break;
	}

    /*新建失败*/
	if (!scene) {
		return;
	}

    /*新建成功，通过导演启动场景（初始场景）或切换场景*/
	Director* director = Director::getInstance();
	if (!director->getRunningScene()) {
		director->runWithScene(scene);
	}
	else {
		director->replaceScene(scene);
	}
}