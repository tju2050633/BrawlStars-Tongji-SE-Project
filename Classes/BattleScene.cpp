#include "BattleScene.h"
#include <vector>
using namespace std;
USING_NS_CC;

/* ����ս������ͼ */
Scene* BattleScene::createScene()
{
	Scene* scene = Scene::create();
	BattleScene* layer = BattleScene::create();
	scene->addChild(layer);
	return scene;
}


/* ��ʼ������ */
bool BattleScene::init()
{
	if (!Layer::init())
	{
		log("BattleScene init failed");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* ��ӵ�ͼ */
	_tileMap = TMXTiledMap::create("TileGameResources/TileMap.tmx");
	_background = _tileMap->getLayer("Background");
	this->addChild(_tileMap);

	/* ���ǽ��ͼ�� */
	_wall = _tileMap->getLayer("Wall");

	/* �������ͼ�㲢���ɼ��� */
	_meta = _tileMap->getLayer("Meta");
	_meta->setVisible(false);

	/* ��Ӳݴ�ͼ�� */
	_grass = _tileMap->getLayer("Grass");

	/* ��ȡ��ͼ�ж���� */
	TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");

	if (!objectGroup)
	{
		log("tile map has no objects object layer");
		return  false;
	}

	/* ��ȡ������������㼴������ */
	auto spawnPoint = objectGroup->getObject("SpawnPoint"); //������
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	/*******************************************
			   ������Һ����滻
	********************************************/
	/* ������ */
	_player = new Sprite();
	_player->initWithFile("TileGameResources/Player.png");
	_player->setPosition(Vec2(x, y));
	this->addChild(_player);
	this->setViewPointCenter(_player->getPosition());
	this->playerMove();

	return true;
}


/* ���ô��ھ�ͷλ�� */
void BattleScene::setViewPointCenter(Point position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* ��ֹ��ҳ����߽� */
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - visibleSize.height / 2);

	Point actualPosition = Vec2(x, y);
	Point centerOfView = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Point viewPoint = Vec2(centerOfView.x - actualPosition.x, centerOfView.y - actualPosition.y);
	this->setPosition(viewPoint);
}


/**************************
	 ���������ƶ�����
*******************************/
void BattleScene::playerMove()
{
	Vec2 playerPos = _player->getPosition(); //��ʱʹ������λ�ò���
	this->setPlayerPosition(playerPos); //�������λ�ã�������ײ��
	this->setGrassOpacity(playerPos); //���òݴ�͸����
}


/* ������ת��Ϊtile���� */
Point BattleScene::tileCoordForPosition(Point position)
{
	//tilemap�����Ͻ�Ϊ����(0,0)
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;

	return Vec2(x, y);
}


/* �������λ�ã����������ײ */
void BattleScene::setPlayerPosition(Point position)
{
	Vec2 tileSize = _tileMap->getTileSize(); //��õ�����Ƭ�ߴ�
	Point pos = Vec2(position.x + 1.7 * tileSize.x, position.y + tileSize.y); //����λ��ƫ��

	Point tileCoord = this->tileCoordForPosition(pos); //ͨ��ָ�������Ӧtile����
	if (_wall->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ��ǽ�ڵ�Ԫ��
	{
		return; //��ǽ�巢����ײʱ���ƶ�
	}
	_player->setPosition(position);
}


/* ���òݴ�͸���� */
void BattleScene::setGrassOpacity(Point position)
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

	Vec2 tileSize = _tileMap->getTileSize(); //��õ�����Ƭ�ߴ�

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



/************************************
    δ��ɣ�����ϴ��з�Χʹ��
************************************/
/* ǽ�ڱ����дݻ� */
void BattleScene::breakWall(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position); //ͨ��ָ�������Ӧtile����
	if (_wall->getTileAt(tileCoord)) //���ͨ��tile�����ܹ�����ָ��ǽ�ڵ�Ԫ��
	{
		_wall->removeTileAt(tileCoord); //�Ƴ��õ�Ԫ�񣬱�ʾǽ�ڱ�ը��
	}
}