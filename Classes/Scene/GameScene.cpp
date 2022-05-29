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
//init����ܲ�����������CREATE_FUNC�Զ����ɵ�create()
//������ģ�壨�����init�ڲ�����Ч����create()һ����
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

/*��Ϸ��������ʼ��*/
bool GameScene::init()
{
	/*��ʼ������*/
	if (!Layer::init())
	{
		return false;
	}

	/*���������SimpleAudioEngine���ڿ��Ǽ��ϻ��ǻ����*/
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
	//audio->playBackgroundMusic("ѡ���ͼ��������", true);
	//}

	/*��ʼ�� ��ͼ�������������ť�����أ����飩��������*/
	initMap();
	initBrawler();
	initLabel();
	initButton();
	initController();

	this->scheduleUpdate();

	return true;
}

/*ÿ֡ˢ��*/
void GameScene::update(float dt)
{
	/*ÿ֡����Ŀ��λ�ã�����ǰλ��+�ٶ�*ÿ֡ʱ��������ƶ���*/
	Vec2 playerPos = _player->getTargetPosition() +
		Vec2(_player->getTargetMoveSpeedX() * dt, _player->getTargetMoveSpeedY() * dt);
	setPlayerPosition(playerPos);//�������λ��
	this->setGrassOpacity(_player->getPosition());//���òݴ�͸����
	this->setViewPointCenter(_player->getPosition());//���þ�ͷ����
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

	/* �������ͼ�㲢���ɼ��� */
	_meta = _map->getLayer("Meta");
	_meta->setVisible(false);

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

/*��ʼ�� ��ǩ*/
void GameScene::initLabel()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

	auto label = Label::createWithTTF(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str(), "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(1, 1));
	label->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y));

	this->addChild(label);
}

/*��ʼ�� ��ť*/
void GameScene::initButton()
{
	/*��ȡvisibleSize��origin*/
	auto visibleSize = Director::getInstance()->getVisibleSize(); //�õ���Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	  //��ÿ�������ĳ��������꣬�ڴ������λ��ʱ��ȷ���ڵ��ڲ�ͬ�ֱ����µ�λ��һ�¡�

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
		Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y - 250),
		Vec2(origin.x, visibleSize.height + origin.y) };
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
	this->addChild(menu, 1);
}

/*��ʼ�� ������*/
void GameScene::initController()
{
	/*����������*/
	_playerController = PlayerController::create();
	/*�����Ϊ�������Ķ���*/
	_playerController->setControllerListener(_player);

	this->addChild(_playerController);
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* ��ֹ��ҳ����߽� */
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height) - visibleSize.height / 2);

	Point actualPosition = Vec2(x, y);
	Point centerOfView = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Point viewPoint = Vec2(centerOfView.x - actualPosition.x, centerOfView.y - actualPosition.y);

	this->setPosition(viewPoint);
}

/* ������ת��Ϊtile���� */
Point GameScene::tileCoordForPosition(Point position)
{
	//tilemap�����Ͻ�Ϊ����(0,0)
	int x = position.x / _map->getTileSize().width;
	int y = ((_map->getMapSize().height * _map->getTileSize().height) - position.y) / _map->getTileSize().height;

	return Vec2(x, y);
}

/* �������λ�ã����������ײ */
void GameScene::setPlayerPosition(Point position)
{
	Vec2 tileSize = _map->getTileSize(); //��õ�����Ƭ�ߴ�
	Point pos = Vec2(position.x + 2.5 * tileSize.x, position.y + 2.3 * tileSize.y); //����λ��ƫ��
	
	Point tileCoord = this->tileCoordForPosition(pos); //ͨ��ָ�������Ӧtile����
	if (_wall->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ��ǽ�ڵ�Ԫ��
	{
		return; //��ǽ�巢����ײʱ���ƶ�
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

	Point pos = Vec2(position.x + 1.7 * tileSize.x, position.y + tileSize.y); //����λ��ƫ��
	vision =
	{
		pos,
		Vec2(pos.x + tileSize.x, pos.y),
		Vec2(pos.x - tileSize.x, pos.y),
		Vec2(pos.x, pos.y + tileSize.y),
		Vec2(pos.x, pos.y - tileSize.y)
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
	}
}