#ifndef __BATTLESCENE_H
#define __BATTLESCENE_H

#include "cocos2d.h"
USING_NS_CC; //编译器使用cocos2d命名空间，省略cocos2d::

/* 战斗场景类 */
class BattleScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(BattleScene);
	virtual bool init();
	/****************************
		 玩家移动：完成后需替换
	*******************************/
	void playerMove(); //玩家移动函数
	virtual void setViewPointCenter(Point position); //设置窗口镜头位置
	Point tileCoordForPosition(Point position); //转化为tile坐标
	void setPlayerPosition(Point position); //设置玩家位置（添加物理碰撞）
	void setGrassOpacity(Point position); //设置草丛透明度
	void breakWall(Point position); //墙壁被大招摧毁

	/************************************************************************************/
	void initMap();
	void initPlayer();
	void initKeyboardListener();

	/*键盘监听器*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);
	/*键盘监听回调函数*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float dt) override;

	int _moveSpeedX;
	int _moveSpeedY;
	/************************************************************************************/

private:
	TMXTiledMap* _tileMap; //战斗地图.tmx格式
	TMXLayer* _background; //背景层
	TMXLayer* _wall; //墙壁图层
	Sprite* _wallCell; //墙壁单元格
	Sprite* _player; //玩家
	TMXLayer* _meta; //属性图层
	TMXLayer* _grass; //草丛图层
	Sprite* _grassCell; //草丛单元格

	TMXObjectGroup* _objectGroup;/* 地图中对象层 */
};


#endif __BATTLESCENE_H
