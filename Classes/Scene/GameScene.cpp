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
	mapLayer->initEmotionMenu();
	mapLayer->initControllerSprite();
	mapLayer->initController();

	/*将地图层、UI层添加到场景中*/
	scene->addChild(mapLayer);
	scene->addChild(UILayer);
	return scene;
}

/*************************************************************初始化UI层组件*************************************************************/

/*UI层 标签*/
void GameScene::initLabel()
{
	_label = Label::createWithTTF(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str(), "fonts/arial.ttf", 48);
	_label->setAnchorPoint(Vec2(1, 1));
	_label->setPosition(Vec2(_visibleSize.width + _origin.x, _visibleSize.height + _origin.y));

	_UILayer->addChild(_label);
}

/*UI层 按钮*/
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

/*UI层 表情菜单*/
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
		/*创建*/
		MenuItem* item = MenuItemImage::create(
			"Emotion/" + brawlerName + "/" + brawlerName + "_" + stringVector.at(i) + ".png",
			"Emotion/" + brawlerName + "/" + brawlerName + "_" + stringVector.at(i) + ".png",
			[=](Ref* sender) {
				/*表情菜单隐藏*/
				_emotionMenu->setVisible(false);
				/*移除旧表情，创建新表情*/
				_player->removeChildByName("Emotion");
				auto emotion = Sprite::createWithTexture(Director::getInstance()->getTextureCache()
					->addImage("Emotion/" + brawlerName + "/" + brawlerName + "_" + stringVector.at(i) + ".png"));
				/*设置尺寸*/
				emotion->setScaleX(80 / emotion->getContentSize().width);
				emotion->setScaleY(80 / emotion->getContentSize().height);
				/*设置位置*/
				emotion->setPosition(Vec2(0, 100));
				_player->addChild(emotion, 1, "Emotion");
				/*定时器*/
				scheduleOnce([&](float dt) {
					_player->removeChildByName("Emotion");
					}, 2.0f, "removeEmotion");
			});
		/*设置尺寸*/
		item->setScaleX(80 / item->getContentSize().width);
		item->setScaleY(80 / item->getContentSize().height);
		/*设置位置*/
		Vec2 position = Vec2(_origin.x + _visibleSize.width, _origin.y + _visibleSize.height / 2);
		if (i <= 3)
			item->setPosition(position + Vec2(-400 + i * 100, 100));
		else
			item->setPosition(position + Vec2(-400 + (i - 4) * 100, 0));
		
		/*存入数组*/
		EmotionVector.pushBack(item);
	}
	/*放置*/
	_emotionMenu = Menu::createWithArray(EmotionVector);
	_emotionMenu->setPosition(Vec2::ZERO);
	_emotionMenu->setVisible(false);

	_UILayer->addChild(_emotionMenu, 2);
}

/*UI层 控制器图标*/
void GameScene::initControllerSprite()
{
	/*方向控制器*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/Controller.plist");
	_controllerSprite = Sprite::createWithSpriteFrameName("Controller-Normal.png");
	_controllerSprite->setScale(0.6);
	_controllerSprite->setAnchorPoint(Vec2(0, 0));
	_controllerSprite->setPosition(Vec2(-150, -150));

	_UILayer->addChild(_controllerSprite);

	/*攻击和技能图标*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Controller/AttackButton.plist");
	/*攻击 大圆*/
	auto attackRoundSprite = Sprite::createWithSpriteFrameName("AttackRound.png");
	attackRoundSprite->setScale(0.6);
	attackRoundSprite->setPosition(Vec2(_visibleSize.width + _origin.x - 150, _origin.y + 200));

	_UILayer->addChild(attackRoundSprite);

	/*攻击 小圆*/
	_attackCenterSprite = Sprite::createWithSpriteFrameName("AttackCenter.png");
	_attackCenterSprite->setScale(0.6);
	_attackCenterSprite->setPosition(attackRoundSprite->getPosition() - Vec2(0, 80));
	_attackCenterSprite->setOpacity(150);

	_UILayer->addChild(_attackCenterSprite);

	/*技能 大圆*/
	_abilityRoundSprite = Sprite::createWithSpriteFrameName("AbilityRound.png");
	_abilityRoundSprite->setScale(0.6);
	_abilityRoundSprite->setPosition(attackRoundSprite->getPosition() - Vec2(140, 0));
	_abilityRoundSprite->setVisible(false);

	_UILayer->addChild(_abilityRoundSprite);

	/*技能 小圆*/
	_abilityCenterSprite = Sprite::createWithSpriteFrameName("Ability.png");
	_abilityCenterSprite->setScale(0.6);
	_abilityCenterSprite->setAnchorPoint(Vec2(0.5, 0.5));
	_abilityCenterSprite->setPosition(_abilityRoundSprite->getPosition() - Vec2(45, 80));

	_UILayer->addChild(_abilityCenterSprite);
}

/*UI层 控制器*/
void GameScene::initController()
{
	/*创建控制器*/
	_playerController = PlayerController::create();

	/*绑定玩家为操作器的对象*/
	_playerController->setControllerListener(_player);
	_player->getBrawler()->setPlayerController(_playerController);

	/*绑定操作器的图标*/
	_playerController->setControllerSprite(_controllerSprite);
	_playerController->setAttackCenterSprite(_attackCenterSprite);
	_playerController->setAbilityCenterSprite(_abilityCenterSprite);
	_playerController->setAbilityRoundSprite(_abilityRoundSprite);

	/*保存攻击和技能图标的原位置*/
	_playerController->setAttackCenterOriginPosition(_attackCenterSprite->getPosition());
	_playerController->setAbilityCenterOriginPosition(_abilityCenterSprite->getPosition());

	/*储存菜单项矩形，防误点*/
	_playerController->setRectReturnButton(CCRectMake(_returnButton->getPosition().x, _returnButton->getPosition().y - _returnButton->getContentSize().height,
		_returnButton->getContentSize().width, _returnButton->getContentSize().height));
	_playerController->setRectEmotionButton(CCRectMake(_emotionButton->getPosition().x - _emotionButton->getContentSize().width, _emotionButton->getPosition().y - _emotionButton->getContentSize().height,
		_emotionButton->getContentSize().width, _emotionButton->getContentSize().height));

	this->addChild(_playerController, 0, "controller");
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
	
	this->scheduleUpdate();						//每帧刷新
	this->schedule([=](float dt) {				//每1秒刷新
		for (auto brawler : _brawlerVector)
		{
			/*如果在毒雾中，受到伤害*/
			smokeDamage(brawler->getParent()->getPosition(), brawler);
			/*如果离上次受伤和攻击超过5s，回血*/
			if (brawler->getReadyForHeal())
				brawler->heal(brawler->getHealthPoint() * 0.13);
		}
	}, 1.0f, "smoke damaga/auto heal");

	return true;
}

/*每帧刷新*/
void GameScene::update(float dt)
{
	/*每帧更新玩家位置，即当前位置+速度*每帧时间产生的移动量*/
	Vec2 playerPos = _player->getTargetPosition() + Vec2(_player->getTargetMoveSpeedX() * dt, _player->getTargetMoveSpeedY() * dt);

	this->setPlayerPosition(playerPos);//设置玩家位置
	this->setGrassOpacity(playerPos);//设置草丛透明度
	this->setViewPointCenter(playerPos);//设置镜头跟随
	//this->smokeDamage(playerPos,_player->getBrawler());	//毒烟伤害
}

/*************************************************************初始化地图层*************************************************************/

/*地图层 瓦片地图*/
void GameScene::initMap()
{
	/* 添加地图 */
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

	/* 添加墙壁图层 */
	_wall = _map->getLayer("Wall");

	/* 添加碰撞属性图层并不可见化 */
	_collidable = _map->getLayer("Collidable");
	_collidable->setVisible(false);

	/* 添加草丛图层 */
	_grass = _map->getLayer("Grass");

	/* 添加毒烟图层 */
	_smoke = _map->getLayer("Smoke");
	_xTileCoordMin = 0,
	_xTileCoordMax = _map->getMapSize().width,
	_yTileCoordMin = 0,
	_yTileCoordMax = _map->getMapSize().height;
	this->smokeMove();

	/* 添加宝箱对象层 */
	_boxObjects = _map->getObjectGroup("BoxObjects");
	/* 获取全部宝箱位置 */
	this->getBoxPosition();

	/* 添加玩家出生点坐标对象层 */
	_playerSpawnPoint = _map->getObjectGroup("PlayerSpawnPoint");

	/* 添加AI出生点坐标对象层 */
	_AISpawnPoint = _map->getObjectGroup("AISpawnPoint");
}

/*地图层 人物*/
void GameScene::initBrawler()
{
	//initPlayer
	//initAI

	/*创建Player*/
	_player = Player::create();

	/*绑定英雄*/
	string brawlerName = bindBrawler();
	
	/*英雄所处场景绑定为此游戏场景*/
	_player->getBrawler()->setGameScene(this);

	/*英雄绑定精灵图像*/
	_player->getBrawler()->setSprite(Sprite::create("Portrait/Shelly-Normal.png"));
	_player->getBrawler()->addChild(_player->getBrawler()->getSprite());
	_player->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_Bottom1.png"));

	/*将玩家和AI放置在出生点*/
	placeInSpawnPoint();

	/*镜头移到玩家所在处*/
	setViewPointCenter(_player->getPosition());

	/*添加范围指示器*/
	addRangeIndicator(SceneUtils::_brawler);

	/*添加血条*/
	addBar(_player->getBrawler());

	/*播放英雄开场语音*/
	string filepath = "Music/" + brawlerName + "/" + brawlerName + "_Start.mp3";
	SimpleAudioEngine::getInstance()->playEffect(filepath.c_str());

	/*添加进渲染树和Vector成员变量*/
	_brawlerVector.pushBack(_player->getBrawler());

	this->addChild(_player);
}

/*************************************************************初始化英雄 辅助函数*************************************************************/

/*绑定英雄*/
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

/*放置玩家和AI在出生点*/
void GameScene::placeInSpawnPoint()
{
	/*放置玩家*/
	auto spawnPoint = _playerSpawnPoint->getObject("SpawnPoint"); //出生点
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	_player->setPosition(Vec2(x, y));

	/*放置AI*/
	if (_AISpawnPoint != NULL)
	{
		ValueVector AIGroup = _AISpawnPoint->getObjects(); //获取AI对象层的所有对象
		int size = AIGroup.size();
		for (int i = 0; i < size; i++) //遍历AI对象层所有出生点对象坐标
		{
			ValueMap objInfo = AIGroup.at(i).asValueMap();
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			Point AISpawnPoint = Vec2(x, y); //AI出生点
			/***************************
				在该位置设置AI
			****************************/
		}
	}
}

/*添加范围指示器*/
void GameScene::addRangeIndicator(SceneUtils::AllBrawler brawler)
{
	Sprite* rangeIndicatorAttack;
	Sprite* rangeIndicatorAbility;
	switch (brawler)
	{
	case SceneUtils::Shelly:
		/*攻击*/
		rangeIndicatorAttack = Sprite::create("Controller/sector.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0.53, 0.55));
		rangeIndicatorAttack->setRotation(15);
		/*技能*/
		rangeIndicatorAbility = Sprite::create("Controller/sector.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0.53, 0.55));
		rangeIndicatorAbility->setRotation(15);
		rangeIndicatorAbility->setScale(1.25);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	case SceneUtils::Nita:
		/*攻击*/
		rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.5));
		rangeIndicatorAttack->setScale(0.3);
		/*技能*/
		rangeIndicatorAbility = Sprite::create("Controller/circle.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0.37, 0.5));
		rangeIndicatorAbility->setScale(0.7);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	case SceneUtils::Primo:
		/*攻击*/
		rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.5));
		rangeIndicatorAttack->setScaleX(0.15);
		rangeIndicatorAttack->setScaleY(0.3);
		/*技能*/
		rangeIndicatorAbility = Sprite::create("Controller/circle.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0.37, 0.5));
		rangeIndicatorAbility->setScale(0.7);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	case SceneUtils::Stu:
		/*攻击*/
		rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.55));
		rangeIndicatorAttack->setScale(0.3);
		/*技能*/
		rangeIndicatorAbility = Sprite::create("Controller/rectangle.png");
		rangeIndicatorAbility->setAnchorPoint(Vec2(0, 0.55));
		rangeIndicatorAbility->setScaleX(0.1);
		rangeIndicatorAbility->setScaleY(0.4);
		rangeIndicatorAbility->setColor(Color3B::YELLOW);
		break;
	}
	/*攻击、技能指示器添加到玩家上*/
	_player->getBrawler()->setRangeIndicatorAttack(rangeIndicatorAttack);
	_player->addChild(rangeIndicatorAttack);
	_player->getBrawler()->setRangeIndicatorAbility(rangeIndicatorAbility);
	_player->addChild(rangeIndicatorAbility);
	/*设为不可见*/
	_player->getBrawler()->getRangeIndicatorAttack()->setVisible(false);
	_player->getBrawler()->getRangeIndicatorAbility()->setVisible(false);
}

/*添加血条、子弹条和能量条*/
void GameScene::addBar(Brawler* brawler)
{
	/*血条*/
	auto hpBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("hpBar.png"));
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setScale(0.5, 0.4);
	hpBar->setPosition(Vec2(-50, 55));
	brawler->setHpBar(hpBar);
	brawler->addChild(hpBar);
	brawler->setHpBarSize(hpBar->getContentSize());
	/*血条文字*/
	auto hpBarLabel = Label::createWithTTF(
		StringUtils::format("%d", brawler->getCurrentHealthPoint()).c_str(),
		"fonts/Marker Felt.ttf", 15);
	hpBarLabel->setPosition(Vec2(0, 55));
	brawler->setHpBarLabel(hpBarLabel);
	brawler->addChild(hpBarLabel);
	/*子弹条*/
	auto ammoBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("ammoBar.png"));
	ammoBar->setAnchorPoint(Vec2(0, 0.5));
	ammoBar->setPosition(Vec2(-50, 44));
	ammoBar->setScale(0.09, 0.06);
	brawler->setAmmoBar(ammoBar);
	brawler->addChild(ammoBar);
	brawler->setAmmoBarSize(ammoBar->getContentSize());
	/*能量条*/
	auto energyBar = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("energyBar.png"));
	energyBar->setAnchorPoint(Vec2(0, 0.5));
	energyBar->setScale(0.7, 0.4);
	energyBar->setPosition(Vec2(-50, 35));
	brawler->setEnergyBar(energyBar);
	brawler->addChild(energyBar);
	brawler->setEnergyBarSize(energyBar->getContentSize());
	
	brawler->setEnergeBarPercent(0);	//能量条初始为0
}

/*************************************************************回调函数*************************************************************/

/*表情 回调函数*/
void GameScene::menuEmotionCallback(cocos2d::Ref* pSender)
{
	smokeMove();

	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	if(_emotionMenu->isVisible())
		_emotionMenu->setVisible(false);
	else
		_emotionMenu->setVisible(true);
}

/*返回 回调函数*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/ButtonEffect.wav");
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Menu.mp3");
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

/*************************************************************瓦片地图需要的函数*************************************************************/

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

/* 获取全部宝箱的位置 */
void GameScene::getBoxPosition()
{
	if (_boxObjects != NULL)
	{
		ValueVector boxGroup = _boxObjects->getObjects(); //获取宝箱对象层的所有对象
		for (int i = 0; i < boxGroup.size(); i++)
		{
			ValueMap objInfo = boxGroup.at(i).asValueMap();
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			_boxPos.push_back(Vec2(x, y)); //存储全部宝箱位置坐标
		}
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

/* 毒烟移动(每调用一次毒烟移动一格) */
void GameScene::smokeMove()
{
	/* 全部显示毒烟 */
	for (int X = _xTileCoordMin; X < _xTileCoordMax; X++)
	{
		for (int Y = _yTileCoordMin; Y < _yTileCoordMax; Y++)
		{
			if (_smoke->getTileAt(Vec2(X, Y))) //如果通过tile坐标能够访问指定毒烟单元格
			{
				_smokeCell = _smoke->getTileAt(Vec2(X, Y));
				_smokeCell->setVisible(true);
			}
		}
	}

	/* 毒烟移动 */
	_xTileCoordMin++;
	_xTileCoordMax--;
	_yTileCoordMin++;
	_yTileCoordMax--;

	/* 中心不显示毒烟 */
	for (int X = _xTileCoordMin; X < _xTileCoordMax; X++)
	{
		for (int Y = _yTileCoordMin; Y < _yTileCoordMax; Y++)
		{
			if (_smoke->getTileAt(Vec2(X, Y))) //如果通过tile坐标能够访问指定毒烟单元格
			{
				_smokeCell = _smoke->getTileAt(Vec2(X, Y));
				_smokeCell->setVisible(false);
			}
		}
	}
}

/* 毒烟伤害 */
void GameScene::smokeDamage(Point position, Brawler* brawler)
{
	Point tileCoord = this->tileCoordForPosition(position); //通过指定坐标对应tile坐标
	if (_smoke->getTileAt(tileCoord)) //如果通过tile坐标能够访问指定毒烟单元格
	{
		_smokeCell = _smoke->getTileAt(tileCoord); //通过tile坐标能够访问指定毒烟单元格
		if (_smokeCell->isVisible()) //如果毒烟可见
		{
			brawler->takeDamage(SMOKE_DAMAGE);
		}
	}
}

