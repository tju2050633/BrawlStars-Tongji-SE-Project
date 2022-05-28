#ifndef __BATTLESCENE_H
#define __BATTLESCENE_H

#include "cocos2d.h"
USING_NS_CC; //������ʹ��cocos2d�����ռ䣬ʡ��cocos2d::

/* ս�������� */
class BattleScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(BattleScene);
	virtual bool init();
	/****************************
		 ����ƶ�����ɺ����滻
	*******************************/
	void playerMove(); //����ƶ�����
	virtual void setViewPointCenter(Point position); //���ô��ھ�ͷλ��
	Point tileCoordForPosition(Point position); //ת��Ϊtile����
	void setPlayerPosition(Point position); //�������λ�ã����������ײ��
	void setGrassOpacity(Point position); //���òݴ�͸����
	void breakWall(Point position); //ǽ�ڱ����дݻ�

	/************************************************************************************/
	void initMap();
	void initPlayer();
	void initKeyboardListener();

	/*���̼�����*/
	CC_SYNTHESIZE(EventListenerKeyboard*, _keyboardListener, KeyboardListener);
	/*���̼����ص�����*/
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float dt) override;

	int _moveSpeedX;
	int _moveSpeedY;
	/************************************************************************************/

private:
	TMXTiledMap* _tileMap; //ս����ͼ.tmx��ʽ
	TMXLayer* _background; //������
	TMXLayer* _wall; //ǽ��ͼ��
	Sprite* _wallCell; //ǽ�ڵ�Ԫ��
	Sprite* _player; //���
	TMXLayer* _meta; //����ͼ��
	TMXLayer* _grass; //�ݴ�ͼ��
	Sprite* _grassCell; //�ݴԵ�Ԫ��

	TMXObjectGroup* _objectGroup;/* ��ͼ�ж���� */
};


#endif __BATTLESCENE_H
