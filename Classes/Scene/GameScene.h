#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_

#include "cocos2d.h"
#include <string>
#include "Player/Player.h"
#include "Controller/PlayerController.h"

USING_NS_CC;
using namespace std;

class GameScene : public Layer
{
private:
	/*UI层*/
	Size _visibleSize;
	Vec2 _origin;
	Layer* _UILayer;
	Label* _label;
	Sprite* _controllerSprite;
	/*玩家部分*/
	Player* _player;
	PlayerController* _playerController;
	/*瓦片地图部分*/
	TMXTiledMap* _map;
	TMXLayer* _background;		//背景层
	TMXLayer* _wall;			//墙壁图层
	Sprite* _wallCell;			//墙壁单元格
	TMXLayer* _meta;			//属性图层
	TMXLayer* _grass;			//草丛图层
	Sprite* _grassCell;			//草丛单元格
	TMXObjectGroup* _objectGroup;/* 地图中对象层 */
	
	/*UI层组件*/
	void initLabel();			//标签
	void initButton();			//按钮
	void initControllerSprite(string = "Normal");//控制器图标
	
	/*初始化*/
	void initMap();				//地图
	void initBrawler();			//英雄
	void initController();		//控制器
	
	/*回调函数*/
	void menuEmotionCallback(Ref *pSender);	//显示表情
	void menuBackCallback(Ref *pSender);	//返回主菜单

public:
	/*创建场景和初始化*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void update(float dt);

	/*瓦片地图需要的函数*/
	virtual void setViewPointCenter(Point position); //设置窗口镜头位置
	Point tileCoordForPosition(Point position); //转化为tile坐标
	void setPlayerPosition(Point position); //设置玩家位置（添加物理碰撞）
	void setGrassOpacity(Point position); //设置草丛透明度
	void breakWall(Point position); //墙壁被大招摧毁
};

#endif // !__GAME_SCENE_H_