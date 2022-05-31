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

/*获得场景对象 √*/
Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	/*创建场景的两个互相独立的层：地图层（包含地图、人物等），UI层（包含标签、按钮、操作器图标等）*/
	auto mapLayer = GameScene::create();
	auto UILayer = Layer::create();
	mapLayer->_UILayer = UILayer;	//GameScene类含有UI层的指针，才能调用初始化UI层的成员函数

	/*初始化UI层的UI组件*/
	mapLayer->initLabel();
	mapLayer->initButton();
	mapLayer->initControllerSprite();
	mapLayer->initController();

	/*将地图层、UI层添加到场景中*/
	scene->addChild(mapLayer);
	scene->addChild(UILayer);
	return scene;
}

/*UI层 标签*/
void GameScene::initLabel()
{
	_label = Label::createWithTTF(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str(), "fonts/Marker Felt.ttf", 48);
	_label->setAnchorPoint(Vec2(1, 1));
	_label->setPosition(Vec2(_visibleSize.width + _origin.x, _visibleSize.height + _origin.y));

	_UILayer->addChild(_label);
}

/*UI层 按钮*/
void GameScene::initButton()
{
	/*菜单所有按钮统一处理，必须用用cocos::Vector*/
	Vector<MenuItem*> MenuItemVector;
	//文件名所用的字符串
	vector<string> stringVector = { "Emotion", "Back" };
	//按钮回调函数
	vector<void (GameScene::*)(Ref* pSender)> CallbackVector = { &GameScene::menuEmotionCallback, &GameScene::menuBackCallback };
	//按钮尺寸
	vector<float> ScaleVector = { 1, 1 };
	//按钮锚点
	vector<Vec2> AnchorVector = {
		Vec2(1, 1),
		Vec2(0, 1) };
	//按钮坐标
	vector<Vec2> PositionVector = {
		Vec2(_visibleSize.width + _origin.x, _visibleSize.height + _origin.y - 250),
		Vec2(_origin.x, _visibleSize.height + _origin.y) };
	/*逐个设置坐标，存入Vector*/
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

	/*总的菜单，包含以上菜单选项*/
	Menu* menu = Menu::createWithArray(MenuItemVector);
	menu->setPosition(Vec2::ZERO);
	_UILayer->addChild(menu, 1);
}

/*UI层 控制器图标*/
void GameScene::initControllerSprite(string state)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/Controller.plist");
	_controllerSprite = Sprite::createWithSpriteFrameName("Controller-" + state + ".png");
	_controllerSprite->setScale(0.6);
	_controllerSprite->setAnchorPoint(Vec2(0, 0));
	_controllerSprite->setPosition(Vec2(-150, -150));

	_UILayer->addChild(_controllerSprite);
}

/*控制器*/
void GameScene::initController()
{
	/*创建控制器*/
	_playerController = PlayerController::create();

	/*绑定玩家为操作器的对象*/
	_playerController->setControllerListener(_player);

	/*绑定操作器的图标*/
	_playerController->setControllerSprite(_controllerSprite);

	this->addChild(_playerController);
}

/*游戏主场景初始化*/
bool GameScene::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	/*获取visibleSize和origin*/
	_visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	_origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*初始化*/
	initMap();
	initBrawler();
	//initController();
	
	this->scheduleUpdate();

	return true;
}

/*每帧刷新*/
void GameScene::update(float dt)
{
	/*每帧更新目标位置，即当前位置+速度*每帧时间产生的移动量*/
	Vec2 playerPos = _player->getTargetPosition() +
		Vec2(_player->getTargetMoveSpeedX() * dt, _player->getTargetMoveSpeedY() * dt);

	this->setPlayerPosition(playerPos);//设置玩家位置
	this->setGrassOpacity(playerPos);//设置草丛透明度
	this->setViewPointCenter(playerPos);//设置镜头跟随
}

/*初始化 地图*/
void GameScene::initMap()
{
	/* 添加地图 */
	_map = TMXTiledMap::create("TileGameResources/TileMap.tmx");
	_background = _map->getLayer("Background");
	this->addChild(_map);

	/* 添加墙壁图层 */
	_wall = _map->getLayer("Wall");

	/* 添加碰撞属性图层并不可见化 */
	_collidable = _map->getLayer("Collidable");
	_collidable->setVisible(false);

	/* 添加宝箱图层 */
	_box = _map->getLayer("Box");

	/* 添加草丛图层 */
	_grass = _map->getLayer("Grass");

	/* 获取地图中对象层 */
	_objectGroup = _map->getObjectGroup("Objects");
}

/*初始化 人物*/
void GameScene::initBrawler()
{
	/*创建Player*/
	_player = Player::create();
	/*绑定英雄*/
	_player->setBrawler(Shelly::create());
	_player->addChild(_player->getBrawler());
	/*英雄绑定精灵图像*/
	_player->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly-Normal.png"));
	_player->setScale(0.1);

	/*将玩家放置在出生点*/
	auto spawnPoint = _objectGroup->getObject("SpawnPoint"); //出生点
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	_player->setPosition(Vec2(x, y));
	/*镜头移到玩家所在处*/
	setViewPointCenter(_player->getPosition());

	this->addChild(_player);
}

/*表情 回调函数*/
void GameScene::menuEmotionCallback(cocos2d::Ref* pSender)
{
}

/*菜单 返回回调函数 √*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

/* 设置窗口镜头位置 */
void GameScene::setViewPointCenter(Point position)
{
	/* 防止玩家超出边界 */
	int x = MAX(position.x, _visibleSize.width / 2);
	int y = MAX(position.y, _visibleSize.height / 2);
	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width * 1500 / 1600) - _visibleSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height * 1195.3 / 1280) - _visibleSize.height / 2);

	Point actualPosition = Vec2(x, y);
	Point centerOfView = Vec2(_visibleSize.width / 2, _visibleSize.height / 2);
	Point viewPoint = Vec2(centerOfView.x - actualPosition.x, centerOfView.y - actualPosition.y);

	this->setPosition(viewPoint);
}

/* 将坐标转化为tile坐标 */
Point GameScene::tileCoordForPosition(Point position)
{
	//消除位置偏差
	double X = position.x * 1600 / 1500;
	double Y = position.y * 1280 / 1195.3;
	
	//tilemap以左上角为坐标(0,0)
	int x = X / _map->getTileSize().width;
	int y = ((_map->getMapSize().height * _map->getTileSize().height) - Y) / _map->getTileSize().height;

	return Vec2(x, y);
}

/* 设置玩家位置，添加物理碰撞 */
void GameScene::setPlayerPosition(Point position)
{
	Vec2 tileSize = _map->getTileSize(); //获得单个瓦片尺寸

	Point tileCoord = this->tileCoordForPosition(position); //通过指定坐标对应tile坐标
	if (_collidable->getTileAt(tileCoord)) //如果通过tile坐标能够访问指定碰撞属性单元格
	{
		return; //与物体发生碰撞时不移动
	}
	_player->setPosition(position);
}

/* 设置草丛透明度 */
void GameScene::setGrassOpacity(Point position)
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

	Vec2 tileSize = _map->getTileSize(); //获得单个瓦片尺寸

	vision =
	{
		position,
		Vec2(position.x + tileSize.x, position.y),
		Vec2(position.x - tileSize.x, position.y),
		Vec2(position.x, position.y + tileSize.y),
		Vec2(position.x, position.y - tileSize.y)
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

/* 墙壁被大招摧毁 */
void GameScene::breakWall(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position); //通过指定坐标对应tile坐标
	if (_wall->getTileAt(tileCoord)) //如果通过tile坐标能够访问指定墙壁单元格
	{
		_wall->removeTileAt(tileCoord); //移除该单元格，表示墙壁被炸毁
		_collidable->removeTileAt(tileCoord);
	}
}

/* 设置敌人是否可见 */
void GameScene::setEnemyVisible(Sprite* _enemy)
{
	Point position = _enemy->getPosition(); //得到敌人的坐标
	Point tileCoord = this->tileCoordForPosition(position); //通过指定坐标对应tile坐标
	if (_grass->getTileAt(tileCoord)) //如果玩家处于草丛中
	{
		_grassCell = _grass->getTileAt(tileCoord); //通过tile坐标指定草丛单元格
		if (_grassCell->getOpacity() == 255) //敌人不在玩家可视范围内
		{
			_enemy->setVisible(false); //敌人不可见
		}
		else //敌人在玩家可视范围内
		{
			_enemy->setVisible(true); //敌人可见
		}
	}
	else //如果玩家不处于草丛中
	{
		_enemy->setVisible(true); //敌人可见
	}
}