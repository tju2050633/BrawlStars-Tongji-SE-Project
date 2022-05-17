#include "Scene/SceneManager.h"
#include "Scene/OpeningAnimation.h"
#include "Scene/GameMenu.h"
#include "Scene/Settings.h"
#include "Scene/Instruction.h"
#include "Scene/SelectMap.h"
#include "Scene/SelectBrawler.h"
#include "Scene/GameScene.h"
#include "Scene/SceneInfo.h"

/*��������ָ���ʼ��Ϊnullptr*/
SceneManager* SceneManager::_sceneManager = nullptr;

/*�˵���Ϣ��̬��������ʼ��Ϊ��*/
string SceneInfo::map = "";
string SceneInfo::brawler = "";


/*��ȡ���������ָ��*/
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

/*���಻��Ҫ��ʼ�������Ƿ���true*/
bool SceneManager::init() {
	return true;
}

/*�л�����ʱʹ�ã�����Ϊ�ö�����ö����*/
void SceneManager::changeScene(AllScenes targetScene) {
	Scene* scene = nullptr;

    /*���ݲ����½�����*/
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

    /*�½�ʧ��*/
	if (!scene) {
		return;
	}

    /*�½��ɹ���ͨ������������������ʼ���������л�����*/
	Director* director = Director::getInstance();
	if (!director->getRunningScene()) {
		director->runWithScene(scene);
	}
	else {
		director->replaceScene(scene);
	}
}