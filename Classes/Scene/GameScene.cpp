#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <string>
#include "Scene/GameScene.h"
#include "Utils/SceneUtils.h"
#include "Player/Player.h"
#include "Player/AI.h"
#include "Brawler/Shelly.h"
#include "Brawler/Nita.h"
#include "Brawler/Primo.h"
#include "Brawler/Stu.h"
#include "Controller/PlayerController.h"
#include "Constant/Const.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

/*��ó������� ��*/
Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	/*����������������������Ĳ㣺��ͼ�㣨������ͼ������ȣ���UI�㣨������ǩ����ť��������ͼ��ȣ�*/
	auto mapLayer = GameScene::create();
	auto UILayer = Layer::create();
	mapLayer->_UILayer = UILayer;	//GameScene�ຬ��UI���ָ�룬���ܵ��ó�ʼ��UI��ĳ�Ա����

	/*��ʼ��UI���UI���*/
	mapLayer->initLabel();
	mapLayer->initButton();
	mapLayer->initEmotionMenu();
	mapLayer->initControllerSprite();
	mapLayer->initController();

	/*����ͼ�㡢UI����ӵ�������*/
	scene->addChild(mapLayer);
	scene->addChild(UILayer);
	return scene;
}

/*************************************************************��ʼ��UI�����*************************************************************/

/*UI�� ��ǩ*/
void GameScene::initLabel()
{
	_label = Label::createWithTTF(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str(), "fonts/arial.ttf", 48);
	_label->setAnchorPoint(Vec2(1, 1));
	_label->setPosition(Vec2(_visibleSize.width + _origin.x, _visibleSize.height + _origin.y));

	_UILayer->addChild(_label);
}

/*UI�� ��ť*/
void GameScene::initButton()
{
	_emotionButton = MenuItemImage::create("button/Emotion-Normal.png", "button/Emotion-Active.png", bind(&GameScene::menuEmotionCallback, this, std::placeholders::_1));
	_emotionButton->setAnchorPoint(Vec2(1, 1));
	_emotionButton->setPosition(Vec2(_visibleSize.width + _origin.x, _visibleSize.height + _origin.y - 250));
	_emotionButton->setOpacity(200);

	_returnButton = MenuItemImage::create("button/Back-Normal.png", "button/Back-Active.png", bind(&GameScene::menuBackCallback, this, std::placeholders::_1));
	_returnButton->setAnchorPoint(Vec2(0, 1));
	_returnButton->setPosition(Vec2(_origin.x, _visibleSize.height + _origin.y));

	Menu* menu = Menu::create(_emotionButton, _returnButton, NULL);
	menu->setPosition(Vec2::ZERO);
	_UILayer->addChild(menu, 1);
}

/*UI�� ����˵�*/
void GameScene::initEmotionMenu()
{
	string brawlerName;
	switch (SceneUtils::_brawler)
	{
	case SceneUtils::Shelly:
		brawlerName = "Shelly";
		break;
	case SceneUtils::Nita:
		brawlerName = "Nita";
		break;
	case SceneUtils::Primo:
		brawlerName = "Primo";
		break;
	case SceneUtils::Stu:
		brawlerName = "Stu";
		break;
	}

	Vector<MenuItem*> EmotionVector;
	vector<string> stringVector = { "Neutral","Happy", "GG", "Angry", "Sad", "Phew", "Thanks" };

	for (int i = 0; i < 7; i++)
	{
		/*����*/
		MenuItem* item = MenuItemImage::create(
			"Emotion/" + brawlerName + "/" + brawlerName + "_" + stringVector.at(i) + ".png",
			"Emotion/" + brawlerName + "/" + brawlerName + "_" + stringVector.at(i) + ".png",
			[=](Ref* sender) {
				/*����˵�����*/
				_emotionMenu->setVisible(false);
				/*�Ƴ��ɱ��飬�����±���*/
				_player->removeChildByName("Emotion");
				auto emotion = Sprite::createWithTexture(Director::getInstance()->getTextureCache()
					->addImage("Emotion/" + brawlerName + "/" + brawlerName + "_" + stringVector.at(i) + ".png"));
				/*���óߴ�*/
				emotion->setScaleX(80 / emotion->getContentSize().width);
				emotion->setScaleY(80 / emotion->getContentSize().height);
				/*����λ��*/
				emotion->setPosition(Vec2(0, 100));
				_player->addChild(emotion, 1, "Emotion");
				/*��ʱ��*/
				scheduleOnce([&](float dt) {
					_player->removeChildByName("Emotion");
					}, 2.0f, "removeEmotion");
			});
		/*���óߴ�*/
		item->setScaleX(80 / item->getContentSize().width);
		item->setScaleY(80 / item->getContentSize().height);
		/*����λ��*/
		Vec2 position = Vec2(_origin.x + _visibleSize.width, _origin.y + _visibleSize.height / 2);
		if (i <= 3)
			item->setPosition(position + Vec2(-400 + i * 100, 100));
		else
			item->setPosition(position + Vec2(-400 + (i - 4) * 100, 0));
		
		/*��������*/
		EmotionVector.pushBack(item);
	}
	/*����*/
	_emotionMenu = Menu::createWithArray(EmotionVector);
	_emotionMenu->setPosition(Vec2::ZERO);
	_emotionMenu->setVisible(false);

	_UILayer->addChild(_emotionMenu, 2);
}

/*UI�� ������ͼ��*/
void GameScene::initControllerSprite()
{
	/*���������*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/Controller.plist");
	_controllerSprite = Sprite::createWithSpriteFrameName("Controller-Normal.png");
	_controllerSprite->setScale(0.6);
	_controllerSprite->setAnchorPoint(Vec2(0, 0));
	_controllerSprite->setPosition(Vec2(-150, -150));

	_UILayer->addChild(_controllerSprite);

	/*�����ͼ���ͼ��*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/AttackButton.plist");
	/*���� ��Բ*/
	auto attackRoundSprite = Sprite::createWithSpriteFrameName("AttackRound.png");
	attackRoundSprite->setScale(0.6);
	attackRoundSprite->setPosition(Vec2(_visibleSize.width + _origin.x - 150, _origin.y + 200));

	_UILayer->addChild(attackRoundSprite);

	/*���� СԲ*/
	_attackCenterSprite = Sprite::createWithSpriteFrameName("AttackCenter.png");
	_attackCenterSprite->setScale(0.6);
	_attackCenterSprite->setPosition(attackRoundSprite->getPosition() - Vec2(0, 80));
	_attackCenterSprite->setOpacity(150);

	_UILayer->addChild(_attackCenterSprite);

	/*���� ��Բ*/
	_abilityRoundSprite = Sprite::createWithSpriteFrameName("AbilityRound.png");
	_abilityRoundSprite->setScale(0.6);
	_abilityRoundSprite->setPosition(attackRoundSprite->getPosition() - Vec2(140, 0));
	_abilityRoundSprite->setVisible(false);

	_UILayer->addChild(_abilityRoundSprite);

	/*���� СԲ*/
	_abilityCenterSprite = Sprite::createWithSpriteFrameName("Ability.png");
	_abilityCenterSprite->setScale(0.6);
	_abilityCenterSprite->setAnchorPoint(Vec2(0.5, 0.5));
	_abilityCenterSprite->setPosition(_abilityRoundSprite->getPosition() - Vec2(45, 80));

	_UILayer->addChild(_abilityCenterSprite);
}

/*UI�� ������*/
void GameScene::initController()
{
	/*����������*/
	_playerController = PlayerController::create();

	/*�����Ϊ�������Ķ���*/
	_playerController->setControllerListener(_player);
	_player->getBrawler()->setPlayerController(_playerController);

	/*�󶨲�������ͼ��*/
	_playerController->setControllerSprite(_controllerSprite);
	_playerController->setAttackCenterSprite(_attackCenterSprite);
	_playerController->setAbilityCenterSprite(_abilityCenterSprite);
	_playerController->setAbilityRoundSprite(_abilityRoundSprite);

	/*���湥���ͼ���ͼ���ԭλ��*/
	_playerController->setAttackCenterOriginPosition(_attackCenterSprite->getPosition());
	_playerController->setAbilityCenterOriginPosition(_abilityCenterSprite->getPosition());

	/*����˵�����Σ������*/
	_playerController->setRectReturnButton(CCRectMake(_returnButton->getPosition().x, _returnButton->getPosition().y - _returnButton->getContentSize().height,
		_returnButton->getContentSize().width, _returnButton->getContentSize().height));
	_playerController->setRectEmotionButton(CCRectMake(_emotionButton->getPosition().x - _emotionButton->getContentSize().width, _emotionButton->getPosition().y - _emotionButton->getContentSize().height,
		_emotionButton->getContentSize().width, _emotionButton->getContentSize().height));

	this->addChild(_playerController, 0, "controller");
}

/*��Ϸ��������ʼ��*/
bool GameScene::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	/*��ȡvisibleSize��origin*/
	_visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	_origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�
	
	/*��ʼ��*/
	initMap();
	initBrawler();
	
	this->scheduleUpdate();						//ÿ֡ˢ��
	this->schedule([=](float dt) {				//ÿ1��ˢ��
		for (auto brawler : _brawlerVector)
		{
			/*����ڶ����У��ܵ��˺�*/
			smokeDamage(brawler->getParent()->getPosition(), brawler);
			/*������ϴ����˺͹�������5s����Ѫ*/
			if (brawler->getReadyForHeal())
				brawler->heal(brawler->getHealthPoint() * 0.13);
		}
	}, 1.0f, "smoke damaga/auto heal");

	return true;
}

/*ÿ֡ˢ��*/
void GameScene::update(float dt)
{
	/*ÿ֡�������λ�ã�����ǰλ��+�ٶ�*ÿ֡ʱ��������ƶ���*/
	Vec2 playerPos = _player->getTargetPosition() + Vec2(_player->getTargetMoveSpeedX() * dt, _player->getTargetMoveSpeedY() * dt);

	this->setPlayerPosition(playerPos);//�������λ��
	this->setGrassOpacity(playerPos);//���òݴ�͸����
	this->setViewPointCenter(playerPos);//���þ�ͷ����
	//this->smokeDamage(playerPos,_player->getBrawler());	//�����˺�
}

/*************************************************************��ʼ����ͼ��*************************************************************/

/*��ͼ�� ��Ƭ��ͼ*/
void GameScene::initMap()
{
	/* ��ӵ�ͼ */
	switch (SceneUtils::_map)
	{
	case SceneUtils::MapA:
		_map = TMXTiledMap::create("TileGameResources/TileMap1.tmx");
		break;
	case SceneUtils::MapB:
		_map = TMXTiledMap::create("TileGameResources/TileMap2.tmx");
		break;
	case SceneUtils::MapC:
		_map = TMXTiledMap::create("TileGameResources/TileMap3.tmx");
		break;
	}
	_background = _map->getLayer("Background");
	this->addChild(_map);

	/* ���ǽ��ͼ�� */
	_wall = _map->getLayer("Wall");

	/* �����ײ����ͼ�㲢���ɼ��� */
	_collidable = _map->getLayer("Collidable");
	_collidable->setVisible(false);

	/* ��Ӳݴ�ͼ�� */
	_grass = _map->getLayer("Grass");

	/* ��Ӷ���ͼ�� */
	_smoke = _map->getLayer("Smoke");
	_xTileCoordMin = 0,
	_xTileCoordMax = _map->getMapSize().width,
	_yTileCoordMin = 0,
	_yTileCoordMax = _map->getMapSize().height;
	this->smokeMove();

	/* ��ӱ������� */
	_boxObjects = _map->getObjectGroup("BoxObjects");
	/* ��ȡȫ������λ�� */
	this->getBoxPosition();

	/* �����ҳ������������� */
	_playerSpawnPoint = _map->getObjectGroup("PlayerSpawnPoint");

	/* ���AI�������������� */
	_AISpawnPoint = _map->getObjectGroup("AISpawnPoint");
}

/*��ͼ�� ����*/
void GameScene::initBrawler()
{
	//initPlayer
	//initAI

	/*����Player*/
	_player = Player::create();

	/*��Ӣ��*/
	string brawlerName = bindBrawler();
	
	/*Ӣ������������Ϊ����Ϸ����*/
	_player->getBrawler()->setGameScene(this);

	/*Ӣ�۰󶨾���ͼ��*/
	_player->getBrawler()->setSprite(Sprite::create("Portrait/Shelly-Normal.png"));
	_player->getBrawler()->addChild(_player->getBrawler()->getSprite());
	_player->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_Bottom1.png"));

	/*����Һ�AI�����ڳ�����*/
	placeInSpawnPoint();

	/*��ͷ�Ƶ�������ڴ�*/
	setViewPointCenter(_player->getPosition());

	/*��ӷ�Χָʾ��*/
	addRangeIndicator(SceneUtils::_brawler);

	/*���Ѫ��*/
	addBar(_player->getBrawler());

	/*����Ӣ�ۿ�������*/
	string filepath = "Music/" + brawlerName + "/" + brawlerName + "_Start.mp3";
	SimpleAudioEngine::getInstance()->playEffect(filepath.c_str());

	/*��ӽ���Ⱦ����Vector��Ա����*/
	_brawlerVector.pushBack(_player->getBrawler());

	this->addChild(_player);
}

/*************************************************************��ʼ��Ӣ�� ��������*************************************************************/

/*��Ӣ��*/
string GameScene::bindBrawler()
{
	string brawlerName;
	switch (SceneUtils::_brawler)
	{
	case SceneUtils::Shelly:
		_player->setBrawler(Shelly::create());
		brawlerName = "Shelly";
		break;
	case SceneUtils::Nita:
		_player->setBrawler(Nita::create());
		brawlerName = "Nita";
		break;
	case SceneUtils::Primo:
		_player->setBrawler(Primo::create());
		brawlerName = "Primo";
		break;
	case SceneUtils::Stu:
		_player->setBrawler(Stu::create());
		brawlerName = "Stu";
		break;
	default:
		break;
	}
	_player->addChild(_player->getBrawler());
	_player->getBrawler()->setIsPlayer(true);

	return brawlerName;
}

/*������Һ�AI�ڳ�����*/
void GameScene::placeInSpawnPoint()
{
	/*�������*/
	auto spawnPoint = _playerSpawnPoint->getObject("SpawnPoint"); //������
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	_player->setPosition(Vec2(x, y));

	/*����AI*/
	if (_AISpawnPoint != NULL)
	{
		ValueVector AIGroup = _AISpawnPoint->getObjects(); //��ȡAI���������ж���
		int size = AIGroup.size();
		for (int i = 0; i < size; i++) //����AI��������г������������
		{
			ValueMap objInfo = AIGroup.at(i).asValueMap();
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			Point AISpawnPoint = Vec2(x, y); //AI������
			/***************************
				�ڸ�λ������AI
			****************************/
		}
	}
}

/*��ӷ�Χָʾ��*/
void GameScene::addRangeIndicator(SceneUtils::AllBrawler brawler)
{
	Sprite* rangeIndicatorAttack;
	Sprite* rangeIndicatorAbility;
	switch (brawler)
	{
	case SceneUtils::Shelly:
		/*����*/
		rangeIndicatorAttack = Sprite::create("Controller/sector.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0.53, 0.55));
		rangeIndicatorAttack->setRotation(15);
		/*����*/
		rangeIndicatorAbility = Sprite::create("Controller/sector.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0.53, 0.55));
		rangeIndicatorAbility->setRotation(15);
		rangeIndicatorAbility->setScale(1.25);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	case SceneUtils::Nita:
		/*����*/
		rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.5));
		rangeIndicatorAttack->setScale(0.3);
		/*����*/
		rangeIndicatorAbility = Sprite::create("Controller/circle.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0.37, 0.5));
		rangeIndicatorAbility->setScale(0.7);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	case SceneUtils::Primo:
		/*����*/
		rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.5));
		rangeIndicatorAttack->setScaleX(0.15);
		rangeIndicatorAttack->setScaleY(0.3);
		/*����*/
		rangeIndicatorAbility = Sprite::create("Controller/circle.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0.37, 0.5));
		rangeIndicatorAbility->setScale(0.7);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	case SceneUtils::Stu:
		/*����*/
		rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.55));
		rangeIndicatorAttack->setScale(0.3);
		/*����*/
		rangeIndicatorAbility = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0, 0.55));
		rangeIndicatorAbility->setScaleX(0.1);
		rangeIndicatorAbility->setScaleY(0.4);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	}
	/*����������ָʾ����ӵ������*/
	_player->getBrawler()->setRangeIndicatorAttack(rangeIndicatorAttack);
	_player->addChild(rangeIndicatorAttack);
	_player->getBrawler()->setRangeIndicatorAbility(rangeIndicatorAbility);
	_player->addChild(rangeIndicatorAbility);
	/*��Ϊ���ɼ�*/
	_player->getBrawler()->getRangeIndicatorAttack()->setVisible(false);
	_player->getBrawler()->getRangeIndicatorAbility()->setVisible(false);
}

/*���Ѫ�����ӵ�����������*/
void GameScene::addBar(Brawler* brawler)
{
	/*Ѫ��*/
	auto hpBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"));
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setScale(0.5, 0.4);
	hpBar->setPosition(Vec2(-50, 55));
	brawler->setHpBar(hpBar);
	brawler->addChild(hpBar);
	brawler->setHpBarSize(hpBar->getContentSize());
	/*Ѫ������*/
	auto hpBarLabel = Label::createWithTTF(
		StringUtils::format("%d", brawler->getCurrentHealthPoint()).c_str(),
		"fonts/Marker Felt.ttf", 15);
	hpBarLabel->setPosition(Vec2(0, 55));
	brawler->setHpBarLabel(hpBarLabel);
	brawler->addChild(hpBarLabel);
	/*�ӵ���*/
	auto ammoBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ammoBar.png"));
	ammoBar->setAnchorPoint(Vec2(0, 0.5));
	ammoBar->setPosition(Vec2(-50, 44));
	ammoBar->setScale(0.09, 0.06);
	brawler->setAmmoBar(ammoBar);
	brawler->addChild(ammoBar);
	brawler->setAmmoBarSize(ammoBar->getContentSize());
	/*������*/
	auto energyBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("energyBar.png"));
	energyBar->setAnchorPoint(Vec2(0, 0.5));
	energyBar->setScale(0.7, 0.4);
	energyBar->setPosition(Vec2(-50, 35));
	brawler->setEnergyBar(energyBar);
	brawler->addChild(energyBar);
	brawler->setEnergyBarSize(energyBar->getContentSize());
	
	brawler->setEnergeBarPercent(0);	//��������ʼΪ0
}

/*************************************************************�ص�����*************************************************************/

/*���� �ص�����*/
void GameScene::menuEmotionCallback(cocos2d::Ref* pSender)
{
	smokeMove();

	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	if(_emotionMenu->isVisible())
		_emotionMenu->setVisible(false);
	else
		_emotionMenu->setVisible(true);
}

/*���� �ص�����*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Menu.mp3");
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

/*************************************************************��Ƭ��ͼ��Ҫ�ĺ���*************************************************************/

/* ���ô��ھ�ͷλ�� */
void GameScene::setViewPointCenter(Point position)
{
	/* ��ֹ��ҳ����߽� */
	int x = MAX(position.x, _visibleSize.width / 2);
	int y = MAX(position.y, _visibleSize.height / 2);
	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width * 1500 / 1600) - _visibleSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height * 1195.3 / 1280) - _visibleSize.height / 2);

	Point actualPosition = Vec2(x, y);
	Point centerOfView = Vec2(_visibleSize.width / 2, _visibleSize.height / 2);
	Point viewPoint = Vec2(centerOfView.x - actualPosition.x, centerOfView.y - actualPosition.y);

	this->setPosition(viewPoint);
}

/* ������ת��Ϊtile���� */
Point GameScene::tileCoordForPosition(Point position)
{
	//����λ��ƫ��
	double X = position.x * 1600 / 1500;
	double Y = position.y * 1280 / 1195.3;
	
	//tilemap�����Ͻ�Ϊ����(0,0)
	int x = X / _map->getTileSize().width;
	int y = ((_map->getMapSize().height * _map->getTileSize().height) - Y) / _map->getTileSize().height;

	return Vec2(x, y);
}

/* �������λ�ã����������ײ */
void GameScene::setPlayerPosition(Point position)
{
	Vec2 tileSize = _map->getTileSize(); //��õ�����Ƭ�ߴ�

	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_collidable->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ����ײ���Ե�Ԫ��
	{
		return; //�����巢����ײʱ���ƶ�
	}
	_player->setPosition(position);
}

/* ���òݴ�͸���� */
void GameScene::setGrassOpacity(Point position)
{
	static vector<Point> vision = {}; //ʹ�þ�̬�����������ƶ�λ�ú�ԭ�ݴ�

	/* ʹ֮ǰλ���Ͽ��ӵĲݴԻָ���͸��״̬ */
	int i; //���ڱ���vision����
	for (i = 0; i < vision.size(); i++)
	{
		Point tileCoord = this->tileCoordForPosition(vision[i]); //ͨ��ָ�������Ӧtile����
		if (_grass->getTileAt(tileCoord))
		{
			_grassCell = _grass->getTileAt(tileCoord); //ͨ��tile�������ָ���ݴԵ�Ԫ��
			_grassCell->setOpacity(255); //��ָ���ݴԵ�Ԫ����Ϊ��͸��
		}
	}

	Vec2 tileSize = _map->getTileSize(); //��õ�����Ƭ�ߴ�

	vision =
	{
		position,
		Vec2(position.x + tileSize.x, position.y),
		Vec2(position.x - tileSize.x, position.y),
		Vec2(position.x, position.y + tileSize.y),
		Vec2(position.x, position.y - tileSize.y)
	}; //��ҿ��ӲݴԷ�Χ�����λ�ü������ĸ�

	/* ʹ��ҿ��ӷ�Χ�ڵĲݴԱ�Ϊ��͸�� */
	for (i = 0; i < vision.size(); i++)
	{
		Point tileCoord = this->tileCoordForPosition(vision[i]); //ͨ��ָ�������Ӧtile����
		if (_grass->getTileAt(tileCoord))
		{
			_grassCell = _grass->getTileAt(tileCoord); //ͨ��tile����ָ���ݴԵ�Ԫ��
			_grassCell->setOpacity(100); //��ָ���ݴԵ�Ԫ����Ϊ��͸��
		}
	}
}

/* ǽ�ڱ����дݻ� */
void GameScene::breakWall(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_wall->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ��ǽ�ڵ�Ԫ��
	{
		_wall->removeTileAt(tileCoord); //�Ƴ��õ�Ԫ�񣬱�ʾǽ�ڱ�ը��
		_collidable->removeTileAt(tileCoord);
	}
}

/* ��ȡȫ�������λ�� */
void GameScene::getBoxPosition()
{
	if (_boxObjects != NULL)
	{
		ValueVector boxGroup = _boxObjects->getObjects(); //��ȡ������������ж���
		for (int i = 0; i < boxGroup.size(); i++)
		{
			ValueMap objInfo = boxGroup.at(i).asValueMap();
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			_boxPos.push_back(Vec2(x, y)); //�洢ȫ������λ������
		}
	}
}

/* ���õ����Ƿ�ɼ� */
void GameScene::setEnemyVisible(Sprite* _enemy)
{
	Point position = _enemy->getPosition(); //�õ����˵�����
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_grass->getTileAt(tileCoord)) //�����Ҵ��ڲݴ���
	{
		_grassCell = _grass->getTileAt(tileCoord); //ͨ��tile����ָ���ݴԵ�Ԫ��
		if (_grassCell->getOpacity() == 255) //���˲�����ҿ��ӷ�Χ��
		{
			_enemy->setVisible(false); //���˲��ɼ�
		}
		else //��������ҿ��ӷ�Χ��
		{
			_enemy->setVisible(true); //���˿ɼ�
		}
	}
	else //�����Ҳ����ڲݴ���
	{
		_enemy->setVisible(true); //���˿ɼ�
	}
}

/* �����ƶ�(ÿ����һ�ζ����ƶ�һ��) */
void GameScene::smokeMove()
{
	/* ȫ����ʾ���� */
	for (int X = _xTileCoordMin; X < _xTileCoordMax; X++)
	{
		for (int Y = _yTileCoordMin; Y < _yTileCoordMax; Y++)
		{
			if (_smoke->getTileAt(Vec2(X, Y))) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
			{
				_smokeCell = _smoke->getTileAt(Vec2(X, Y));
				_smokeCell->setVisible(true);
			}
		}
	}

	/* �����ƶ� */
	_xTileCoordMin++;
	_xTileCoordMax--;
	_yTileCoordMin++;
	_yTileCoordMax--;

	/* ���Ĳ���ʾ���� */
	for (int X = _xTileCoordMin; X < _xTileCoordMax; X++)
	{
		for (int Y = _yTileCoordMin; Y < _yTileCoordMax; Y++)
		{
			if (_smoke->getTileAt(Vec2(X, Y))) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
			{
				_smokeCell = _smoke->getTileAt(Vec2(X, Y));
				_smokeCell->setVisible(false);
			}
		}
	}
}

/* �����˺� */
void GameScene::smokeDamage(Point position, Brawler* brawler)
{
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_smoke->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
	{
		_smokeCell = _smoke->getTileAt(tileCoord); //ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
		if (_smokeCell->isVisible()) //������̿ɼ�
		{
			brawler->takeDamage(SMOKE_DAMAGE);
		}
	}
}

