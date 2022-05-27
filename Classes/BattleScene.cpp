#include "BattleScene.h"
#include <vector>
using namespace std;
USING_NS_CC;

/* 创建战斗场景图 */
Scene* BattleScene::createScene()
{
	Scene* scene = Scene::create();
	BattleScene* layer = BattleScene::create();
	scene->addChild(layer);
	return scene;
}


/* 初始化场景 */
bool BattleScene::init()
{
	if (!Layer::init())
	{
		log("BattleScene init failed");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* 添加地图 */
	_tileMap = TMXTiledMap::create("TileGameResources/TileMap.tmx");
	_background = _tileMap->getLayer("Background");
	this->addChild(_tileMap);

	/* 添加墙壁图层 */
	_wall = _tileMap->getLayer("Wall");

	/* 添加属性图层并不可见化 */
	_meta = _tileMap->getLayer("Meta");
	_meta->setVisible(false);

	/* 添加草丛图层 */
	_grass = _tileMap->getLayer("Grass");

	/* 获取地图中对象层 */
	TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");

	if (!objectGroup)
	{
		log("tile map has no objects object layer");
		return  false;
	}

	/* 获取对象层对象出生点即其坐标 */
	auto spawnPoint = objectGroup->getObject("SpawnPoint"); //出生点
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	/*******************************************
			   创建玩家后需替换
	********************************************/
	/* 添加玩家 */
	_player = new Sprite();
	_player->initWithFile("TileGameResources/Player.png");
	_player->setPosition(Vec2(x, y));
	this->addChild(_player);
	this->setViewPointCenter(_player->getPosition());
	this->playerMove();

	return true;
}


/* 设置窗口镜头位置 */
void BattleScene::setViewPointCenter(Point position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* 防止玩家超出边界 */
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
	 需调用玩家移动函数
*******************************/
void BattleScene::playerMove()
{
	Vec2 playerPos = _player->getPosition(); //暂时使用现有位置测试
	this->setPlayerPosition(playerPos); //设置玩家位置（考虑碰撞）
	this->setGrassOpacity(playerPos); //设置草丛透明度
}


/* 将坐标转化为tile坐标 */
Point BattleScene::tileCoordForPosition(Point position)
{
	//tilemap以左上角为坐标(0,0)
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;

	return Vec2(x, y);
}


/* 设置玩家位置，添加物理碰撞 */
void BattleScene::setPlayerPosition(Point position)
{
	Vec2 tileSize = _tileMap->getTileSize(); //获得单个瓦片尺寸
	Point pos = Vec2(position.x + 1.7 * tileSize.x, position.y + tileSize.y); //消除位置偏差

	Point tileCoord = this->tileCoordForPosition(pos); //通过指定坐标对应tile坐标
	if (_wall->getTileAt(tileCoord)) //如果通过tile坐标能够访问指定墙壁单元格
	{
		return; //与墙体发生碰撞时不移动
	}
	_player->setPosition(position);
}


/* 设置草丛透明度 */
void BattleScene::setGrassOpacity(Point position)
{
	static vector<Point> vision = {}; //使用静态变量，便于移动位置后复原草丛

	/* 使之前位置上可视的草丛恢复不透明状态 */
	int i; //用于遍历vision容器
	for (i = 0; i < vision.size(); i++)
	{
		Point tileCoord = this->tileCoordForPosition(vision[i]); //通过指定坐标对应tile坐标
		if (_grass->getTileAt(tileCoord))
		{
			_grassCell = _grass->getTileAt(tileCoord); //通过tile坐标访问指定草丛单元格
			_grassCell->setOpacity(255); //将指定草丛单元格设为不透明
		}
	}

	Vec2 tileSize = _tileMap->getTileSize(); //获得单个瓦片尺寸

	Point pos = Vec2(position.x + 1.7 * tileSize.x, position.y + tileSize.y); //消除位置偏差
	vision =
	{
		pos,
		Vec2(pos.x + tileSize.x, pos.y),
		Vec2(pos.x - tileSize.x, pos.y),
		Vec2(pos.x, pos.y + tileSize.y),
		Vec2(pos.x, pos.y - tileSize.y)
	}; //玩家可视草丛范围（玩家位置即相邻四格）
	
	/* 使玩家可视范围内的草丛变为半透明 */
	for (i = 0; i < vision.size(); i++)
	{
		Point tileCoord = this->tileCoordForPosition(vision[i]); //通过指定坐标对应tile坐标
		if (_grass->getTileAt(tileCoord))
		{
			_grassCell = _grass->getTileAt(tileCoord); //通过tile坐标指定草丛单元格
			_grassCell->setOpacity(100); //将指定草丛单元格设为半透明
		}
	}
}



/************************************
    未完成：需配合大招范围使用
************************************/
/* 墙壁被大招摧毁 */
void BattleScene::breakWall(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position); //通过指定坐标对应tile坐标
	if (_wall->getTileAt(tileCoord)) //如果通过tile坐标能够访问指定墙壁单元格
	{
		_wall->removeTileAt(tileCoord); //移除该单元格，表示墙壁被炸毁
	}
}