#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_

#include "cocos2d.h"
#include <string>
#include <vector>
#include "Player/Player.h"
#include "Player/AI.h"
#include "Controller/PlayerController.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;
using namespace std;

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
	Sprite* _controllerSprite;	//方向控制器
	Sprite* _attackCenterSprite;//攻击键中心
	Sprite* _abilityCenterSprite;//技能键中心
	Sprite* _abilityRoundSprite; //技能键底盘
	/*玩家部分*/
	Player* _player;
	Vector<AI*> _AI_Vector;
	Vector<Brawler*> _brawlerVector;
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
	void initControllerSprite();//控制器图标
	void initController();		//控制器
	
	/*初始化地图层*/
	void initMap();				//地图
	void initBrawler();			//英雄

	/*初始化英雄 辅助函数*/
	string bindBrawler();									//绑定英雄，返回英雄名称字符串
	void placeInSpawnPoint();								//放置玩家和AI在出生点
	void addRangeIndicator(SceneUtils::AllBrawler brawler);	//添加范围指示器
	void addBar(Brawler* brawler);						//添加血条
	
	/*回调函数*/
	void menuEmotionCallback(Ref *pSender);	//显示表情
	void menuBackCallback(Ref *pSender);	//返回主菜单

public:
	static GameScene* _gameScene;
	/*创建场景和初始化*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	static GameScene* getGameScene() { return _gameScene; }
	void update(float dt);

	/*瓦片地图需要的函数*/
	virtual void setViewPointCenter(Point position); //设置窗口镜头位置
	Point tileCoordForPosition(Point position);	     //转化为tile坐标
	void setPlayerPosition(Point position);          //设置玩家位置（添加物理碰撞）
	void setGrassOpacity(Point position);            //设置草丛透明度
	void breakWall(Point position);                  //墙壁被大招摧毁
	bool isWallTile(Point position);                  //判断该位置是否为墙体

	void setEnemyVisible(Sprite* _enemy);            //设置敌人是否可见
	void getBoxPosition();                           //获取全部宝箱的位置
	void boxDie(Point position);                     //宝箱被摧毁（死亡）
	void smokeMove();                                //毒烟移动
	void smokeDamage(Point position, Brawler* brawler);//毒烟伤害

	/*对外提供接口*/
	Size getTileSize()const { return _map->getTileSize(); }
};

#endif // !__GAME_SCENE_H_