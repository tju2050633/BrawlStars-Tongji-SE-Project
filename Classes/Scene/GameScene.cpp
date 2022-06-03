#include "cocos2d.h"
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

USING_NS_CC;
using namespace std;

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
	mapLayer->initControllerSprite();
	mapLayer->initController();

	/*����ͼ�㡢UI����ӵ�������*/
	scene->addChild(mapLayer);
	scene->addChild(UILayer);
	return scene;
}

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
	/*�˵����а�ťͳһ������������cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//�ļ������õ��ַ���
	vector<string> stringVector = { "Emotion", "Back" };
	//��ť�ص�����
	vector<void (GameScene::*)(Ref* pSender)> CallbackVector = { &GameScene::menuEmotionCallback, &GameScene::menuBackCallback };
	//��ť�ߴ�
	vector<float> ScaleVector = { 1, 1 };
	//��ťê��
	vector<Vec2> AnchorVector = {
		Vec2(1, 1),
		Vec2(0, 1) };
	//��ť����
	vector<Vec2> PositionVector = {
		Vec2(_visibleSize.width + _origin.x, _visibleSize.height + _origin.y - 250),
		Vec2(_origin.x, _visibleSize.height + _origin.y) };
	/*����������꣬����Vector*/
	for (int i = 0; i < stringVector.size(); i++)
	{
		MenuItem* button = MenuItemImage::create(
			"button/" + stringVector.at(i) + "-Normal.png",
			"button/" + stringVector.at(i) + "-Active.png",
			bind(CallbackVector.at(i), this, std::placeholders::_1));
		if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
			SceneUtils::problemLoading(stringVector.at(i).c_str());
		else
		{
			button->setScale(ScaleVector.at(i));
			button->setAnchorPoint(AnchorVector.at(i));
			button->setPosition(PositionVector.at(i));
		}
		MenuItemVector.pushBack(button);
	}

	/*�ܵĲ˵����������ϲ˵�ѡ��*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	_UILayer->addChild(menu, 1);
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

/*������*/
void GameScene::initController()
{
	/*����������*/
	_playerController = PlayerController::create();

	/*�����Ϊ�������Ķ���*/
	_playerController->setControllerListener(_player);

	/*�󶨲�������ͼ��*/
	_playerController->setControllerSprite(_controllerSprite);
	_playerController->setAttackCenterSprite(_attackCenterSprite);
	_playerController->setAbilityCenterSprite(_abilityCenterSprite);
	_playerController->setAbilityRoundSprite(_abilityRoundSprite);
	/*���湥���ͼ���ͼ���ԭλ��*/
	_playerController->setAttackCenterOriginPosition(_attackCenterSprite->getPosition());
	_playerController->setAbilityCenterOriginPosition(_abilityCenterSprite->getPosition());

	this->addChild(_playerController);
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
	initAI();
	//initController();
	
	this->scheduleUpdate();

	return true;
}

/*ÿ֡ˢ��*/
void GameScene::update(float dt)
{
	/*ÿ֡����Ŀ��λ�ã�����ǰλ��+�ٶ�*ÿ֡ʱ��������ƶ���*/
	Vec2 playerPos = _player->getTargetPosition() + Vec2(_player->getTargetMoveSpeedX() * dt, _player->getTargetMoveSpeedY() * dt);

	this->setPlayerPosition(playerPos);  //�������λ��
	this->setGrassOpacity(playerPos);    //���òݴ�͸����
	this->setViewPointCenter(playerPos); //���þ�ͷ����
	this->smokeDamage(playerPos);        //���̶�����˺�

	_label->setString(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str());//ˢ��Label��ʾ����
}

/*��ʼ�� ��ͼ*/
void GameScene::initMap()
{
	/* ��ӵ�ͼ */
	_map = TMXTiledMap::create("TileGameResources/TileMap.tmx");
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
	this->smokeMove();

	/* ��ӱ���ͼ�� */
	_box = _map->getLayer("Box");

	/* ��ӱ������� */
	_boxObjects = _map->getObjectGroup("BoxObjects");
	/* ��ȡȫ������λ�� */
	this->getBoxPosition();

	/* �����ҳ������������� */
	_playerSpawnPoint = _map->getObjectGroup("PlayerSpawnPoint");

	/* ���AI�������������� */
	_AISpawnPoint = _map->getObjectGroup("AISpawnPoint");
}

/*��ʼ�� ����*/
void GameScene::initBrawler()
{
	/*����Player*/
	_player = Player::create();

	/*��Ӣ��*/
	_player->setBrawler(Shelly::create());
	_player->addChild(_player->getBrawler());

	/*Ӣ������������Ϊ����Ϸ����*/
	_player->getBrawler()->setGameScene(this);

	/*Ӣ�۰󶨾���ͼ��*/
	_player->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly-Normal.png"));
	_player->getBrawler()->getSprite()->setScale(0.1);

	/*����ҷ����ڳ�����*/
	auto spawnPoint = _playerSpawnPoint->getObject("SpawnPoint"); //������
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	_player->setPosition(Vec2(x, y));

	/*��ͷ�Ƶ�������ڴ�*/
	setViewPointCenter(_player->getPosition());

	/*��ӷ�Χָʾ��*/
	auto rangeIndicator = Sprite::create("Controller/sector.png");
	rangeIndicator->setAnchorPoint(Vec2(0.53, 0.55));
	rangeIndicator->setRotation(15);
	rangeIndicator->setVisible(false);
	_player->getBrawler()->setRangeIndicator(rangeIndicator);
	_player->addChild(rangeIndicator);

	this->addChild(_player);
}

/*��ʼ�� AI*/
void GameScene::initAI()
{
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

/*���� �ص�����*/
void GameScene::menuEmotionCallback(cocos2d::Ref* pSender)
{
}

/*�˵� ���ػص����� ��*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

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

/* ��ȡȫ�������λ�� */
void GameScene::getBoxPosition()
{
	if (_boxObjects != NULL)
	{
		ValueVector boxGroup = _boxObjects->getObjects(); //��ȡ������������ж���
		int size = boxGroup.size();
		for (int i = 0; i < size; i++)
		{
			ValueMap objInfo = boxGroup.at(i).asValueMap();
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			_boxPos.push_back(Vec2(x, y)); //�洢ȫ������λ������
		}
	}
}

/* �������λ�ã����������ײ */
void GameScene::setPlayerPosition(Point position)
{
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

/* ���䱻�ݻ٣������� */
void GameScene::boxDie(Point position) //�������������λ�����꣨��_boxPos�л�ȡ��
{
	/* �ӵ�ͼ���Ƴ����� */
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_box->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ�����䵥Ԫ��
	{
		_box->removeTileAt(tileCoord); //�Ƴ��õ�Ԫ�񣬱�ʾ��������
		_collidable->removeTileAt(tileCoord); //��λ�ò�����������ײӰ��
	}

	/* �ӱ���λ��������ɾ����λ������ */
	for (vector<Point>::iterator i = _boxPos.begin(); i < _boxPos.end(); i++)
	{
		if (*i == position)
		{
			_boxPos.erase(i); //ɾ��������
		}
	}

	/**************************************
	     ����buff/�������Ѷ�����
	****************************************/
}

/* �����ƶ�(ÿ����һ�ζ����ƶ�һ��) */
void GameScene::smokeMove()
{
	/* ��ʼ����λ�� */
	static int
		xTileCoordMin = 0,
		xTileCoordMax = _map->getMapSize().width,
		yTileCoordMin = 0,
		yTileCoordMax = _map->getMapSize().height;

	/* ȫ����ʾ���� */
	for (int X = xTileCoordMin; X < xTileCoordMax; X++)
	{
		for (int Y = yTileCoordMin; Y < yTileCoordMax; Y++)
		{
			if (_smoke->getTileAt(Vec2(X, Y))) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
			{
				_smokeCell = _smoke->getTileAt(Vec2(X, Y));
				_smokeCell->setVisible(true);
			}
		}
	}

	/* �����ƶ� */
	++xTileCoordMin;
	--xTileCoordMax;
	++yTileCoordMin;
	--yTileCoordMax;

	/* ���Ĳ���ʾ���� */
	for (int X = xTileCoordMin; X < xTileCoordMax; X++)
	{
		for (int Y = yTileCoordMin; Y < yTileCoordMax; Y++)
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
void GameScene::smokeDamage(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_smoke->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
	{
		_smokeCell = _smoke->getTileAt(tileCoord); //ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
		if (_smokeCell->isVisible()) //������̿ɼ�
		{
			/**************************
			     ����ڶ���������
			**************************/
		}
	}
}