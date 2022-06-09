#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <string>
#include <fstream>
#include "Scene/GameScene.h"
#include "Utils/SceneUtils.h"
#include "Utils/MusicUtils.h"
#include "Player/Player.h"
#include "Player/AI.h"
#include "Entity/Box.h"
#include "Brawler/Shelly.h"
#include "Brawler/Nita.h"
#include "Brawler/Primo.h"
#include "Brawler/Stu.h"
#include "Controller/PlayerController.h"
#include "Constant/Const.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;
using namespace std;


GameScene* GameScene::_gameScene = nullptr;

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
	mapLayer->initPauseMenu();
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

	_pauseButton = MenuItemImage::create("button/pause_button.png", "button/pause_button.png", bind(&GameScene::menuPause, this, std::placeholders::_1));
	_pauseButton->setAnchorPoint(Vec2(0, 1));
	_pauseButton->setPosition(Vec2(_origin.x, _visibleSize.height + _origin.y));
	_pauseButton->setScale(0.5f);

	Menu* menu = Menu::create(_emotionButton, _pauseButton, NULL);
	menu->setPosition(Vec2::ZERO);
	_UILayer->addChild(menu, 1);
}

/*UI�� ��ͣ�˵�*/
void GameScene::initPauseMenu()
{
	_returnButton = MenuItemImage::create("button/ReturnMenu-Normal.png", "button/ReturnMenu_Active.png", bind(&GameScene::menuBackCallback, this, std::placeholders::_1));
	_returnButton->setAnchorPoint(Vec2(0.5, 0.5));
	_returnButton->setPosition(Vec2(_origin.x + _visibleSize.width / 2, _visibleSize.height / 3 + _origin.y));

	//_returnButton->setScale(0.5f); 

	_musicButton = MenuItemImage::create("button/Music-Normal.png", "button/Music_Active.png", bind(&GameScene::menuMusicCallback, this, std::placeholders::_1));
	_musicButton->setAnchorPoint(Vec2(0.5, 0.5));
	_musicButton->setPosition(Vec2(_origin.x + _visibleSize.width / 2 - _visibleSize.width / 6, _visibleSize.height / 2 + _origin.y));
	//_musicButton->setScale(0.5f);

	_effectButton = MenuItemImage::create("button/Effect-Normal.png", "button/Effect_Active.png", bind(&GameScene::menuEffectCallback, this, std::placeholders::_1));
	_effectButton->setAnchorPoint(Vec2(0.5, 0.5));
	_effectButton->setPosition(Vec2(_origin.x + _visibleSize.width / 2 + _visibleSize.width / 6, _visibleSize.height / 2 + _origin.y));
	//_effectButton->setScale(0.5f);

	_musicText = MenuItemFont::create("ON");
	_musicText->setAnchorPoint(Vec2(0.5, 0.5));
	_musicText->setPosition(Vec2(_origin.x + _visibleSize.width / 2 - _visibleSize.width / 6 + _musicText->getContentSize().width*2, _visibleSize.height / 2 + _origin.y));
	//_musicText->setScale(0.5f);

	_effectText = MenuItemFont::create("ON");
	_effectText->setAnchorPoint(Vec2(0.5, 0.5));
	_effectText->setPosition(Vec2(_origin.x + _visibleSize.width / 2 + _visibleSize.width / 6 + _musicText->getContentSize().width*2, _visibleSize.height / 2 + _origin.y));
	//_effectText->setScale(0.5f);

	Menu* menu = Menu::create(_returnButton, _musicButton, _effectButton, _musicText, _effectText, NULL);
	menu->setPosition(Vec2::ZERO);
	_pauseMenu = menu;
	_UILayer->addChild(menu, 2);
	_pauseMenu->setVisible(false);


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
	_playerController->setRectPauseButton(Rect(_pauseButton->getPosition().x, _pauseButton->getPosition().y - _pauseButton->getContentSize().height,
		_pauseButton->getContentSize().width, _pauseButton->getContentSize().height));
	_playerController->setRectEmotionButton(Rect(_emotionButton->getPosition().x - _emotionButton->getContentSize().width, _emotionButton->getPosition().y - _emotionButton->getContentSize().height,
		_emotionButton->getContentSize().width, _emotionButton->getContentSize().height));
	_playerController->setRectReturnButton(Rect(_returnButton->getPosition().x- _returnButton->getContentSize().width/2, _returnButton->getPosition().y - _returnButton->getContentSize().height / 2,
		_returnButton->getContentSize().width, _returnButton->getContentSize().height));
	_playerController->setRectMusicButton(Rect(_musicButton->getPosition().x - _musicButton->getContentSize().width / 2, _musicButton->getPosition().y - _musicButton->getContentSize().height / 2,
		_musicButton->getContentSize().width, _musicButton->getContentSize().height));
	_playerController->setRectEffectButton(Rect(_effectButton->getPosition().x - _effectButton->getContentSize().width / 2, _effectButton->getPosition().y - _effectButton->getContentSize().height / 2,
		_effectButton->getContentSize().width, _effectButton->getContentSize().height));

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

	_gameScene = this;

	/*��ȡvisibleSize��origin*/
	_visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	_origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	/*��ʼ��*/
	initMap();
	initBrawler();
	//setIsPaused(false);

	this->scheduleUpdate();						//ÿ֡ˢ��

	this->schedule([=](float dt) {				//ÿ1��ˢ��
		for (auto brawler : _brawlerVector)
		{
			/*����ڶ����У��ܵ��˺�;Ӣ��������������*/
			if (smokeDamage(brawler->getParent()->getPosition(), brawler))
				break;
			/*������ϴ����˺͹�������5s����Ѫ*/
			if (brawler->getReadyForHeal())
				brawler->heal(brawler->getHealthPoint() * 0.13);
		}
		}, 1.0f, "smoke damage/auto heal");

	this->schedule([=](float dt) {				//ÿ20��ˢ��
		smokeMove();
		}, SMOKE_MOVE_INTERVAL, "smoke move");

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

	/*��ӱ���*/
	addBox();

	/* �����ҳ������������� */
	_playerSpawnPoint = _map->getObjectGroup("PlayerSpawnPoint");

	/* ���AI�������������� */
	_AISpawnPoint = _map->getObjectGroup("AISpawnPoint");
}

/*��ӱ���*/
void GameScene::addBox()
{
	for (auto pos : _boxPos)
	{
		auto box = Box::create();
		box->bindSprite(Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Box.png")));
		box->setPosition(pos + Vec2(20, 50));
		box->setScale(0.25);
		Entity::initHpBar(box);

		this->addChild(box, 1);
	}
}

/*��ͼ�� ����*/
void GameScene::initBrawler()
{
	/*����Player*/
	_player = Player::create();

	/*��Ӣ��*/
	string brawlerName = bindBrawler();

	/*Ӣ�۰󶨾���ͼ��*/
	_player->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly-Normal.png"));
	_player->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_Bottom1.png"));

	/*����AI*/
	initAI();

	/*����Һ�AI�����ڳ�����*/
	placeInSpawnPoint();

	/*��ͷ�Ƶ�������ڴ�*/
	setViewPointCenter(_player->getPosition());

	/*��ӷ�Χָʾ��*/
	addRangeIndicator(SceneUtils::_brawler);

	/*���Ѫ����*/
	addBar(_player->getBrawler());

	/*����Ӣ�ۿ�������*/
	{
		string filepath = "Music/" + brawlerName + "/" + brawlerName + "_Start.mp3";
		MusicUtils::playEffect(filepath.c_str());

	}

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

/*����AI*/
void GameScene::initAI()
{
	ValueVector AIGroup = _AISpawnPoint->getObjects(); //��ȡAI���������ж���

	//�������AI
	for (int j = 0; j < SceneUtils::_brawlerNumber - 1; j++)
	{
		AI* ai = AI::create();

		//ȷ��AIӢ�����࣬�󶨾���ͼƬ
		if (SceneUtils::_shellyNumber != 0)
		{
			ai->setBrawler(Shelly::create());
			ai->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly-Normal.png"));
			ai->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Shelly_Bottom1.png"));
			SceneUtils::_shellyNumber--;
		}
		else if (SceneUtils::_nitaNumber != 0)
		{
			ai->setBrawler(Nita::create());
			ai->getBrawler()->bindSprite(Sprite::create("Portrait/Nita-Normal.png"));
			ai->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Nita_Bottom1.png"));
			SceneUtils::_nitaNumber--;
		}
		else if (SceneUtils::_primoNumber != 0)
		{
			ai->setBrawler(Primo::create());
			ai->getBrawler()->bindSprite(Sprite::create("Portrait/Primo-Normal.png"));
			ai->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Primo_Bottom1.png"));
			SceneUtils::_primoNumber--;
		}
		else if (SceneUtils::_stuNumber != 0)
		{
			ai->setBrawler(Stu::create());
			ai->getBrawler()->bindSprite(Sprite::create("Portrait/Stu-Normal.png"));
			ai->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Stu_Bottom1.png"));
			SceneUtils::_stuNumber--;
		}

		/*���Ѫ����*/
		addBar(ai->getBrawler());

		//��ӵ���ͼ
		ai->addChild(ai->getBrawler());
		ai->getBrawler()->setIsAI(true);

		_AI_Vector.pushBack(ai);
		this->addChild(ai, 1);
	}
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
		int size = SceneUtils::_brawlerNumber - 1;
		for (int i = 0; i < size; i++) //����AI��������г������������
		{
			ValueMap objInfo = AIGroup.at(i).asValueMap();
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			Point AISpawnPoint = Vec2(x, y); //AI������

			_AI_Vector.at(i)->setPosition(AISpawnPoint);
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
			rangeIndicatorAttack->setAnchorPoint(Vec2(0.55, 0.55));
			rangeIndicatorAttack->setScale(1.8);
			/*����*/
			rangeIndicatorAbility = Sprite::create("Controller/sector.png");
			rangeIndicatorAbility->setAnchorPoint(Vec2(0.57, 0.55));
			rangeIndicatorAbility->setScale(2.7, 1.8);
			rangeIndicatorAbility->setColor(Color3B::YELLOW);
			break;
		case SceneUtils::Nita:
			/*����*/
			rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
			rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.5));
			rangeIndicatorAttack->setScale(0.3);
			/*����*/
			rangeIndicatorAbility = Sprite::create("Controller/circle.png");
			rangeIndicatorAbility->setAnchorPoint(Vec2(0.35, 0.5));
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
			rangeIndicatorAbility->setAnchorPoint(Vec2(0.35, 0.5));
			rangeIndicatorAbility->setScale(1);
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
	Entity::initHpBar(brawler);
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
	/*Buff*/
	auto buff = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Buff.png"));
	buff->setAnchorPoint(Vec2(1, 0.5));
	buff->setScale(0.5);
	buff->setPosition(Vec2(0, 75));
	brawler->addChild(buff);
	/*Buff����*/
	auto buffLabel = Label::createWithTTF(
		StringUtils::format("%d", brawler->getBuffNumber()).c_str(),
		"fonts/Marker Felt.ttf", 20);
	buffLabel->setAnchorPoint(Vec2(0, 0.5));
	buffLabel->setPosition(Vec2(0, 75));
	buffLabel->setColor(Color3B::GREEN);
	brawler->setBuffLabel(buffLabel);
	brawler->addChild(buffLabel);
}

/*************************************************************�ص�����*************************************************************/

/*���� �ص�����*/
void GameScene::menuEmotionCallback(cocos2d::Ref* pSender)
{
	//test
	//smokeMove();

	MusicUtils::playEffect("Music/ButtonEffect.mp3");

	if (_emotionMenu->isVisible())
		_emotionMenu->setVisible(false);
	else
		_emotionMenu->setVisible(true);
}

/*��ͣ �ص�����*/
void GameScene::menuPause(cocos2d::Ref* pSender) 
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");

	if (_pauseMenu->isVisible())
	{
		/*�����ͣ״̬*/
		_pauseMenu->setVisible(false);

		this->initController();//���²��ÿ�����
		_playerController->changeControllerSprite();//���ÿ�����ͼ��

		/*����Ӣ���ж�״̬*/
		AnimationUtils::stopAnimate(_player->getBrawler(), _player->getBrawler()->getAnimateBrawler(), _player->getBrawler()->getDirection());
		_player->setTargetMoveSpeedX(0);
		_player->setTargetMoveSpeedY(0);

		Director::getInstance()->resume();//��������ͣ�ĵ�����
		
	}
	else
	{
		/*��ͣ״̬*/
		_pauseMenu->setVisible(true);

		this->removeChildByName("controller");//�Ƴ�����������ʱ���ֻ����Menu��Ԫ�ػ���

		Director::getInstance()->pause();//��ͣ�����࣬ʹ����schedule������ͣ
	}
}

/*���� �ص�����*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{

	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	MusicUtils::playMusic("Music/Menu.mp3");
	Director::getInstance()->resume();//ʹ��ͣ�ĵ��������������������л�����
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

/*���ֿ��� �ص�����*/
void GameScene::menuMusicCallback(cocos2d::Ref* pSender)
{
	if (MusicUtils::_musicOn == true)
	{
		MusicUtils::_musicOn = false;
		_musicText->setString("OFF");//�ı��ı�
		AudioEngine::pause(MusicUtils::_musicID);//��ͣ��ǰ����
	}
	else if (MusicUtils::_musicOn == false)
	{
		MusicUtils::_musicOn = true;
		_musicText->setString("ON");//�ı��ı�
		AudioEngine::resume(MusicUtils::_musicID);//�������ŵ�ǰ����
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}

/*��Ч���� �ص�����*/
void GameScene::menuEffectCallback(cocos2d::Ref* pSender)
{
	MusicUtils::_effectOn = !MusicUtils::_effectOn;
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	if (MusicUtils::_effectOn == true)
	{
		_effectText->setString("ON");//�ı��ı�
	}
	else if (MusicUtils::_effectOn == false)
	{
		_effectText->setString("OFF");//�ı��ı�
	}
}

/*************************************************************����*************************************************************/

/*Ӣ������*/
void GameScene::BrawlerDie()
{
	SceneUtils::_brawlerNumber--;

	/*��ǩ����*/
	_label->setString(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str());

	/*��������*/
	if (SceneUtils::_brawlerNumber == 2)
	{
		MusicUtils::playMusic("Music/Final.mp3");
	}
}

/*������Ϸ*/
void GameScene::GameOver(bool win)
{
	/*���UI�㣬ֹͣһ��*/
	this->unscheduleAllCallbacks();
	_UILayer->removeFromParent();
	_playerController->removeFromParent();

	/*����*/
	INT32 rank = SceneUtils::_brawlerNumber;
	INT32 trophy;
	switch (rank)
	{
		case 1:
			trophy = 10;
			break;
		case 2:
			trophy = 8;
			break;
		case 3:
			trophy = 7;
			break;
		case 4:
			trophy = 6;
			break;
		case 5:
			trophy = 5;
			break;
		case 6:
			trophy = 4;
			break;
		case 7:
			trophy = 3;
			break;
		case 8:
			trophy = 2;
			break;
		case 9:
			trophy = 0;
			break;
		case 10:
			trophy = 0;
			break;
		default:
			break;
	}

	int iTrophyNumber = 0;
	ifstream in("trophy.txt");
	if (!in.is_open())
	{
		SceneUtils::problemLoading("fail to read iTrophyNumber");
	}
	else {
		in >> iTrophyNumber;
		in.close();
	}

	iTrophyNumber += trophy;

	ofstream out("trophy.txt");
	if (!out.is_open())
	{
		SceneUtils::problemLoading("fail to write iTrophyNumber");
	}
	else {
		out << iTrophyNumber;
		out.close();
	}

	/*BGM�и�*/
	if (win)
		MusicUtils::playMusic("Music/Victory.mp3");
	else if (!win)
		MusicUtils::playMusic("Music/Defeat.mp3");

	/*1��󵯳�/*ʤ��/ʧ�ܻ���*/
	scheduleOnce([=](float dt) {
		/*ʤ����ʧ��ͼ��*/
		Sprite* sprite;
		if (win)
		{
			sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Victory.png"));
			sprite->setScale(4);
		}
		else
		{
			sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Defeat.png"));
			sprite->setScale(2);
		}

		sprite->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
		this->getParent()->addChild(sprite, 2);

		/*���ذ�ť*/
		auto button = MenuItemImage::create("button/ReturnMenu-Normal.png", "button/ReturnMenu-Active.png", CC_CALLBACK_1(GameScene::menuBackCallback, this));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneUtils::problemLoading("button/ReturnMenu-Normal.png");
		else
		{
			button->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 5 + _origin.y));

			Menu* menu = Menu::create(button, NULL);
			menu->setPosition(Vec2::ZERO);
			this->getParent()->addChild(menu, 2);
		}

		//����
		auto rank_label = Label::createWithTTF(StringUtils::format("YOUR RANK : No.%d !", rank).c_str(), "fonts/Marker Felt.ttf", 100);
		rank_label->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height + _origin.y - 130));
		rank_label->setTextColor(Color4B::RED);
		this->getParent()->addChild(rank_label, 1);

		//������������
		auto spr = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("trophy.png"));
		spr->setAnchorPoint(Vec2(0, 1));
		spr->setPosition(Vec2(_origin.x, _visibleSize.height + _origin.y + 10));
		spr->setScale(0.2);
		spr->setRotation(10);
		this->getParent()->addChild(spr, 1);

		auto label = Label::createWithTTF(StringUtils::format("+%d", trophy).c_str(), "fonts/Marker Felt.ttf", 48);
		label->setAnchorPoint(Vec2(0, 1));
		label->setPosition(Vec2(_origin.x + 130, _visibleSize.height + _origin.y - 15));
		label->setTextColor(Color4B::YELLOW);
		this->getParent()->addChild(label, 1);

		}, 1.0f, "displayWIN/LOSE");
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

	//ȷ��������
	if (!(tileCoord.x < 47 && tileCoord.y < 37 && tileCoord.x >= 3 && tileCoord.y >= 3))
		return;

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

	/*Ӣ���ڲݴ����͸��*/
	Point tileCoord = this->tileCoordForPosition(position);
	if (_grass->getTileAt(tileCoord))
	{
		_player->getBrawler()->getSprite()->setOpacity(100);
	}
	else
	{
		_player->getBrawler()->getSprite()->setOpacity(255);
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

/*�жϸ�λ���Ƿ�Ϊǽ��*/
bool GameScene::isWallTile(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_wall->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ��ǽ�ڵ�Ԫ��
		return true;

	return false;
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
bool GameScene::smokeDamage(Point position, Brawler* brawler)
{
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_smoke->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
	{
		_smokeCell = _smoke->getTileAt(tileCoord); //ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
		if (_smokeCell->isVisible()) //������̿ɼ�
		{
			return brawler->takeDamage(SMOKE_DAMAGE);
		}
	}
}


/*ʺɽ�ϵĲ���������ʱ�ӵĽӿ�*/
void GameScene::removeFromBrawlerVector(Brawler* brawler)
{
	for (int i = 0; i < _brawlerVector.size(); i++)
	{
		if (_brawlerVector.at(i) == brawler)
			_brawlerVector.erase(i);
	}
}

void GameScene::removeFromEntityVector(Entity* entity)
{
	for (int i = 0; i < _entityVector.size(); i++)
	{
		if (_entityVector.at(i) == entity)
			_entityVector.erase(i);
	}
}

void GameScene::removeFromBuffVector(Sprite* buff)
{
	for (int i = 0; i < _buffVector.size(); i++)
	{
		if (_buffVector.at(i) == buff)
			_buffVector.erase(i);
	}
}