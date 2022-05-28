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

	initMap();
	initPlayer();
	initKeyboardListener();

	this->scheduleUpdate();

	return true;
}

void BattleScene::initMap()
{
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
	_objectGroup = _tileMap->getObjectGroup("Objects");
}

void BattleScene::initPlayer()
{
	/* 获取对象层对象出生点即其坐标 */
	auto spawnPoint = _objectGroup->getObject("SpawnPoint"); //出生点
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
}

void BattleScene::update(float dt)
{
	/*每帧更新目标位置，即当前位置+速度*每帧时间产生的移动量*/
	_player->setPosition(_player->getPosition() + Vec2(_moveSpeedX * dt, _moveSpeedY * dt));

}

/*初始化键盘监听器*/
void BattleScene::initKeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}

/*键盘监听回调函数*/
void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*按下键盘监听，WASD（及对应大写情况）分别设置对象速度*/
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		_moveSpeedY = 50;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		_moveSpeedX = -50;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		_moveSpeedY = -50;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		_moveSpeedX = 50;
		break;
	default:
		break;
	}
}

void BattleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*松开键盘监听，WASD（及对应大写情况）分别设置对应速度为0*/
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		_moveSpeedY = 0;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		_moveSpeedX = 0;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		_moveSpeedY = 0;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		_moveSpeedX = 0;
		break;
	default:
		break;
	}
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