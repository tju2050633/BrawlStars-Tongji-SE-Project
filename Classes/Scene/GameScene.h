#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_

#include "cocos2d.h"
#include <string>
#include <vector>
#include "Player/Player.h"
#include "Player/AI.h"
#include "Controller/PlayerController.h"
#include "Utils/SceneUtils.h"
#include "ui/UIText.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class GameScene : public Layer
{
private:
	/*UI层*/
	Size _visibleSize;
	Vec2 _origin;
	Layer* _UILayer;
	Label* _label;				//剩余英雄数
	MenuItem* _returnButton;	//返回按钮
	MenuItem* _emotionButton;	//表情按钮
	Menu* _emotionMenu;			//表情菜单

	MenuItem* _pauseButton;	    //暂停按钮
	MenuItem* _musicButton;	    //音乐按钮
	MenuItem* _effectButton;    //音效按钮
	MenuItemFont* _musicText;   //音乐开关文本
	MenuItemFont* _effectText;  //音效开关文本
	Menu* _pauseMenu;			//暂停菜单

	Sprite* _controllerSprite;	//方向控制器
	Sprite* _attackCenterSprite;//攻击键中心
	Sprite* _abilityCenterSprite;//技能键中心
	Sprite* _abilityRoundSprite; //技能键底盘
	/*玩家部分*/
	Player* _player;
	Vector<AI*> _AI_Vector;

	Vector<Brawler*> _brawlerVector;
	Vector<Entity*> _entityVector;
	Vector<Sprite*> _buffVector;

	PlayerController* _playerController;
	/*瓦片地图部分*/
	TMXTiledMap* _map;
	TMXLayer* _background;	 			//背景层
	TMXLayer* _wall;					//墙壁图层
	Sprite* _wallCell;					//墙壁单元格
	TMXLayer* _collidable;				//碰撞属性图层
	TMXLayer* _grass;					//草丛图层
	Sprite* _grassCell;					//草丛单元格
	TMXLayer* _smoke;		         	//毒烟图层
	INT32   _xTileCoordMin;					//毒烟位置
	INT32	_xTileCoordMax;					//毒烟位置
	INT32	_yTileCoordMin;					//毒烟位置
	INT32	_yTileCoordMax;					//毒烟位置
	Sprite* _smokeCell;		            //毒烟单元格
	TMXObjectGroup* _boxObjects;        //宝箱对象层
	vector<Point> _boxPos;              //存储全部宝箱位置坐标
	TMXObjectGroup* _playerSpawnPoint;  //玩家出生点坐标对象层
	TMXObjectGroup* _AISpawnPoint;      //AI出生点坐标对象层
	
	/*初始化UI层组件*/
	void initLabel();			//标签
	void initButton();			//按钮
	void initEmotionMenu();		//表情菜单
	void initPauseMenu();       //暂停菜单
	void initControllerSprite();//控制器图标
	void initController();		//控制器
	
	/*初始化地图层*/
	void initMap();				//地图
	void addBox();				//宝箱
	void initBrawler();			//英雄

	/*初始化英雄 辅助函数*/
	string bindBrawler();									//绑定英雄，返回英雄名称字符串
	
	void initAI();

	void placeInSpawnPoint();								//放置玩家和AI在出生点
	void addRangeIndicator(SceneUtils::AllBrawler brawler);	//添加范围指示器
	void addBar(Brawler* brawler);						//添加血条
	
	/*回调函数*/
	void menuEmotionCallback(Ref *pSender);	//显示表情
	void menuPause(Ref* pSender);	        //呼出暂停菜单
	void menuBackCallback(Ref *pSender);	//返回主菜单
	void menuMusicCallback(Ref* pSender);   //音乐开关
	void menuEffectCallback(Ref* pSender);  //音效开关

public:
	static GameScene* _gameScene;
	/*创建场景和初始化*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	static GameScene* getGameScene() { return _gameScene; }
	void update(float dt);

	/*进程*/
	void BrawlerDie();		//英雄死亡
	void GameOver(bool win);//结束游戏

	/*瓦片地图需要的函数*/
	virtual void setViewPointCenter(Point position); //设置窗口镜头位置
	Point tileCoordForPosition(Point position);	     //转化为tile坐标
	void setTargetPosition(Node* target, Point position);//设置位置（添加物理碰撞）
	void setGrassOpacity(Point position);            //设置草丛透明度
	void breakWall(Point position);                  //墙壁被大招摧毁
	bool isWallTile(Point position);                  //判断该位置是否为墙体

	void setEnemyVisible(Sprite* _enemy);            //设置敌人是否可见
	void getBoxPosition();                           //获取全部宝箱的位置
	void smokeMove();                                //毒烟移动
	bool smokeDamage(Point position, Brawler* brawler);//毒烟伤害

	/*对外提供接口*/
	Size getTileSize()const { return _map->getTileSize(); }
	Layer* getUILayer()const { return _UILayer; }
	Label* getLabel()const { return _label; }
	TMXLayer* getGrass()const { return _grass; }
	void pushBackBrawler(Brawler* brawler) { _brawlerVector.pushBack(brawler); }
	void pushBackEntity(Entity* entity) { _entityVector.pushBack(entity); }
	void pushBackBuff(Sprite* buff) { _buffVector.pushBack(buff); }
	Vector<Brawler*> getBrawlerVector()const { return _brawlerVector; }
	Vector<Entity*> getEntityVector()const { return _entityVector; }
	Vector<Sprite*> getBuffVector()const { return _buffVector; }
	void removeFromBrawlerVector(Brawler* brawler);
	void removeFromEntityVector(Entity* entity);
	void removeFromBuffVector(Sprite* buff);
	void removeFromAIVector(AI* ai);
	TMXLayer* getCollidable()const { return _collidable; }
};

#endif // !__GAME_SCENE_H_