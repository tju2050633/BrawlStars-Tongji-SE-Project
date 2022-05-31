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
	_label = Label::createWithTTF(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str(), "fonts/Marker Felt.ttf", 48);
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
void GameScene::initControllerSprite(string state)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/Controller.plist");
	_controllerSprite = Sprite::createWithSpriteFrameName("Controller-" + state + ".png");
	_controllerSprite->setScale(0.6);
	_controllerSprite->setAnchorPoint(Vec2(0, 0));
	_controllerSprite->setPosition(Vec2(-150, -150));

	_UILayer->addChild(_controllerSprite);
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
	//initController();
	
	this->scheduleUpdate();

	return true;
}

/*ÿ֡ˢ��*/
void GameScene::update(float dt)
{
	/*ÿ֡����Ŀ��λ�ã�����ǰλ��+�ٶ�*ÿ֡ʱ��������ƶ���*/
	Vec2 playerPos = _player->getTargetPosition() +
		Vec2(_player->getTargetMoveSpeedX() * dt, _player->getTargetMoveSpeedY() * dt);

	this->setPlayerPosition(playerPos);//�������λ��
	this->setGrassOpacity(playerPos);//���òݴ�͸����
	this->setViewPointCenter(playerPos);//���þ�ͷ����
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

	/* ��ӱ���ͼ�� */
	_box = _map->getLayer("Box");

	/* ��Ӳݴ�ͼ�� */
	_grass = _map->getLayer("Grass");

	/* ��ȡ��ͼ�ж���� */
	_objectGroup = _map->getObjectGroup("Objects");
}

/*��ʼ�� ����*/
void GameScene::initBrawler()
{
	/*����Player*/
	_player = Player::create();
	/*��Ӣ��*/
	_player->setBrawler(Shelly::create());
	_player->addChild(_player->getBrawler());
	/*Ӣ�۰󶨾���ͼ��*/
	_player->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly-Normal.png"));
	_player->setScale(0.1);

	/*����ҷ����ڳ�����*/
	auto spawnPoint = _objectGroup->getObject("SpawnPoint"); //������
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	_player->setPosition(Vec2(x, y));
	/*��ͷ�Ƶ�������ڴ�*/
	setViewPointCenter(_player->getPosition());

	this->addChild(_player);
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