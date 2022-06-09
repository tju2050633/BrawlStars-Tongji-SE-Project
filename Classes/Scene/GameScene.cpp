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
	mapLayer->initPauseMenu();
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

	_pauseButton = MenuItemImage::create("button/pause_button.png", "button/pause_button.png", bind(&GameScene::menuPause, this, std::placeholders::_1));
	_pauseButton->setAnchorPoint(Vec2(0, 1));
	_pauseButton->setPosition(Vec2(_origin.x, _visibleSize.height + _origin.y));
	_pauseButton->setScale(0.5f);

	Menu* menu = Menu::create(_emotionButton, _pauseButton, NULL);
	menu->setPosition(Vec2::ZERO);
	_UILayer->addChild(menu, 1);
}

/*UI层 暂停菜单*/
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

/*游戏主场景初始化*/
bool GameScene::init()
{
	/*初始化父类*/
	if (!Layer::init())
	{
		return false;
	}

	_gameScene = this;

	/*获取visibleSize和origin*/
	_visibleSize = Director::getInstance()->getVisibleSize(); //得到屏幕大小
	_origin = Director::getInstance()->getVisibleOrigin();	  //获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	/*初始化*/
	initMap();
	initBrawler();
	//setIsPaused(false);

	this->scheduleUpdate();						//每帧刷新

	this->schedule([=](float dt) {				//每1秒刷新
		for (auto brawler : _brawlerVector)
		{
			/*如果在毒雾中，受到伤害;英雄死亡，跳过他*/
			if (smokeDamage(brawler->getParent()->getPosition(), brawler))
				break;
			/*如果离上次受伤和攻击超过5s，回血*/
			if (brawler->getReadyForHeal())
				brawler->heal(brawler->getHealthPoint() * 0.13);
		}
		}, 1.0f, "smoke damage/auto heal");

	this->schedule([=](float dt) {				//每20秒刷新
		smokeMove();
		}, SMOKE_MOVE_INTERVAL, "smoke move");

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

	/*添加宝箱*/
	addBox();

	/* 添加玩家出生点坐标对象层 */
	_playerSpawnPoint = _map->getObjectGroup("PlayerSpawnPoint");

	/* 添加AI出生点坐标对象层 */
	_AISpawnPoint = _map->getObjectGroup("AISpawnPoint");
}

/*添加宝箱*/
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

/*地图层 人物*/
void GameScene::initBrawler()
{
	/*创建Player*/
	_player = Player::create();

	/*绑定英雄*/
	string brawlerName = bindBrawler();

	/*英雄绑定精灵图像*/
	_player->getBrawler()->bindSprite(Sprite::create("Portrait/Shelly-Normal.png"));
	_player->getBrawler()->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_Bottom1.png"));

	/*创建AI*/
	initAI();

	/*将玩家和AI放置在出生点*/
	placeInSpawnPoint();

	/*镜头移到玩家所在处*/
	setViewPointCenter(_player->getPosition());

	/*添加范围指示器*/
	addRangeIndicator(SceneUtils::_brawler);

	/*添加血条等*/
	addBar(_player->getBrawler());

	/*播放英雄开场语音*/
	{
		string filepath = "Music/" + brawlerName + "/" + brawlerName + "_Start.mp3";
		MusicUtils::playEffect(filepath.c_str());

	}

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

/*创建AI*/
void GameScene::initAI()
{
	ValueVector AIGroup = _AISpawnPoint->getObjects(); //获取AI对象层的所有对象

	//逐个创建AI
	for (int j = 0; j < SceneUtils::_brawlerNumber - 1; j++)
	{
		AI* ai = AI::create();

		//确定AI英雄种类，绑定精灵图片
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

		/*添加血条等*/
		addBar(ai->getBrawler());

		//添加到地图
		ai->addChild(ai->getBrawler());
		ai->getBrawler()->setIsAI(true);

		_AI_Vector.pushBack(ai);
		this->addChild(ai, 1);
	}
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
		int size = SceneUtils::_brawlerNumber - 1;
		for (int i = 0; i < size; i++) //遍历AI对象层所有出生点对象坐标
		{
			ValueMap objInfo = AIGroup.at(i).asValueMap();
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			Point AISpawnPoint = Vec2(x, y); //AI出生点

			_AI_Vector.at(i)->setPosition(AISpawnPoint);
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
			rangeIndicatorAttack->setAnchorPoint(Vec2(0.55, 0.55));
			rangeIndicatorAttack->setScale(1.8);
			/*技能*/
			rangeIndicatorAbility = Sprite::create("Controller/sector.png");
			rangeIndicatorAbility->setAnchorPoint(Vec2(0.57, 0.55));
			rangeIndicatorAbility->setScale(2.7, 1.8);
			rangeIndicatorAbility->setColor(Color3B::YELLOW);
			break;
		case SceneUtils::Nita:
			/*攻击*/
			rangeIndicatorAttack = Sprite::create("Controller/rectangle.png");
			rangeIndicatorAttack->setAnchorPoint(Vec2(0, 0.5));
			rangeIndicatorAttack->setScale(0.3);
			/*技能*/
			rangeIndicatorAbility = Sprite::create("Controller/circle.png");
			rangeIndicatorAbility->setAnchorPoint(Vec2(0.35, 0.5));
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
			rangeIndicatorAbility->setAnchorPoint(Vec2(0.35, 0.5));
			rangeIndicatorAbility->setScale(1);
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
	Entity::initHpBar(brawler);
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
	/*Buff*/
	auto buff = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Buff.png"));
	buff->setAnchorPoint(Vec2(1, 0.5));
	buff->setScale(0.5);
	buff->setPosition(Vec2(0, 75));
	brawler->addChild(buff);
	/*Buff文字*/
	auto buffLabel = Label::createWithTTF(
		StringUtils::format("%d", brawler->getBuffNumber()).c_str(),
		"fonts/Marker Felt.ttf", 20);
	buffLabel->setAnchorPoint(Vec2(0, 0.5));
	buffLabel->setPosition(Vec2(0, 75));
	buffLabel->setColor(Color3B::GREEN);
	brawler->setBuffLabel(buffLabel);
	brawler->addChild(buffLabel);
}

/*************************************************************回调函数*************************************************************/

/*表情 回调函数*/
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

/*暂停 回调函数*/
void GameScene::menuPause(cocos2d::Ref* pSender) 
{
	MusicUtils::playEffect("Music/ButtonEffect.mp3");

	if (_pauseMenu->isVisible())
	{
		/*解除暂停状态*/
		_pauseMenu->setVisible(false);

		this->initController();//重新布置控制器
		_playerController->changeControllerSprite();//重置控制器图标

		/*重置英雄行动状态*/
		AnimationUtils::stopAnimate(_player->getBrawler(), _player->getBrawler()->getAnimateBrawler(), _player->getBrawler()->getDirection());
		_player->setTargetMoveSpeedX(0);
		_player->setTargetMoveSpeedY(0);

		Director::getInstance()->resume();//继续被暂停的导演类
		
	}
	else
	{
		/*暂停状态*/
		_pauseMenu->setVisible(true);

		this->removeChildByName("controller");//移除控制器，此时玩家只能与Menu类元素互动

		Director::getInstance()->pause();//暂停导演类，使所有schedule函数暂停
	}
}

/*返回 回调函数*/
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{

	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	MusicUtils::playMusic("Music/Menu.mp3");
	Director::getInstance()->resume();//使暂停的导演类继续活动，才能正常切换场景
	SceneUtils::changeScene(SceneUtils::AllScenes::GameMenu);
}

/*音乐开关 回调函数*/
void GameScene::menuMusicCallback(cocos2d::Ref* pSender)
{
	if (MusicUtils::_musicOn == true)
	{
		MusicUtils::_musicOn = false;
		_musicText->setString("OFF");//改变文本
		AudioEngine::pause(MusicUtils::_musicID);//暂停当前音乐
	}
	else if (MusicUtils::_musicOn == false)
	{
		MusicUtils::_musicOn = true;
		_musicText->setString("ON");//改变文本
		AudioEngine::resume(MusicUtils::_musicID);//继续播放当前音乐
	}
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
}

/*音效开关 回调函数*/
void GameScene::menuEffectCallback(cocos2d::Ref* pSender)
{
	MusicUtils::_effectOn = !MusicUtils::_effectOn;
	MusicUtils::playEffect("Music/ButtonEffect.mp3");
	if (MusicUtils::_effectOn == true)
	{
		_effectText->setString("ON");//改变文本
	}
	else if (MusicUtils::_effectOn == false)
	{
		_effectText->setString("OFF");//改变文本
	}
}

/*************************************************************进程*************************************************************/

/*英雄死亡*/
void GameScene::BrawlerDie()
{
	SceneUtils::_brawlerNumber--;

	/*标签文字*/
	_label->setString(StringUtils::format("Brawler Left: %d", SceneUtils::_brawlerNumber).c_str());

	/*背景音乐*/
	if (SceneUtils::_brawlerNumber == 2)
	{
		MusicUtils::playMusic("Music/Final.mp3");
	}
}

/*结束游戏*/
void GameScene::GameOver(bool win)
{
	/*清除UI层，停止一切*/
	this->unscheduleAllCallbacks();
	_UILayer->removeFromParent();
	_playerController->removeFromParent();

	/*奖杯*/
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

	/*BGM切歌*/
	if (win)
		MusicUtils::playMusic("Music/Victory.mp3");
	else if (!win)
		MusicUtils::playMusic("Music/Defeat.mp3");

	/*1秒后弹出/*胜利/失败画面*/
	scheduleOnce([=](float dt) {
		/*胜利、失败图像*/
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

		/*返回按钮*/
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

		//名次
		auto rank_label = Label::createWithTTF(StringUtils::format("YOUR RANK : No.%d !", rank).c_str(), "fonts/Marker Felt.ttf", 100);
		rank_label->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height + _origin.y - 130));
		rank_label->setTextColor(Color4B::RED);
		this->getParent()->addChild(rank_label, 1);

		//奖杯数量增加
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

	//确保不出界
	if (!(tileCoord.x < 47 && tileCoord.y < 37 && tileCoord.x >= 3 && tileCoord.y >= 3))
		return;

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

	/*英雄在草丛里半透明*/
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

/*判断该位置是否为墙体*/
bool GameScene::isWallTile(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position); //通过指定坐标对应tile坐标
	if (_wall->getTileAt(tileCoord)) //如果通过tile坐标能够访问指定墙壁单元格
		return true;

	return false;
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
bool GameScene::smokeDamage(Point position, Brawler* brawler)
{
	Point tileCoord = this->tileCoordForPosition(position); //通过指定坐标对应tile坐标
	if (_smoke->getTileAt(tileCoord)) //如果通过tile坐标能够访问指定毒烟单元格
	{
		_smokeCell = _smoke->getTileAt(tileCoord); //通过tile坐标能够访问指定毒烟单元格
		if (_smokeCell->isVisible()) //如果毒烟可见
		{
			return brawler->takeDamage(SMOKE_DAMAGE);
		}
	}
}


/*屎山上的补丁——临时加的接口*/
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