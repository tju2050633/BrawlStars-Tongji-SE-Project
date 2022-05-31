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
	/*UI��*/
	Size _visibleSize;
	Vec2 _origin;
	Layer* _UILayer;
	Label* _label;
	Sprite* _controllerSprite;
	/*��Ҳ���*/
	Player* _player;
	PlayerController* _playerController;
	/*��Ƭ��ͼ����*/
	TMXTiledMap* _map;
	TMXLayer* _background;		//������
	TMXLayer* _wall;			//ǽ��ͼ��
	Sprite* _wallCell;			//ǽ�ڵ�Ԫ��
	TMXLayer* _meta;			//����ͼ��
	TMXLayer* _grass;			//�ݴ�ͼ��
	Sprite* _grassCell;			//�ݴԵ�Ԫ��
	TMXObjectGroup* _objectGroup;/* ��ͼ�ж���� */
	
	/*UI�����*/
	void initLabel();			//��ǩ
	void initButton();			//��ť
	void initControllerSprite(string = "Normal");//������ͼ��
	
	/*��ʼ��*/
	void initMap();				//��ͼ
	void initBrawler();			//Ӣ��
	void initController();		//������
	
	/*�ص�����*/
	void menuEmotionCallback(Ref *pSender);	//��ʾ����
	void menuBackCallback(Ref *pSender);	//�������˵�

public:
	/*���������ͳ�ʼ��*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void update(float dt);

	/*��Ƭ��ͼ��Ҫ�ĺ���*/
	virtual void setViewPointCenter(Point position); //���ô��ھ�ͷλ��
	Point tileCoordForPosition(Point position); //ת��Ϊtile����
	void setPlayerPosition(Point position); //�������λ�ã����������ײ��
	void setGrassOpacity(Point position); //���òݴ�͸����
	void breakWall(Point position); //ǽ�ڱ����дݻ�
};

#endif // !__GAME_SCENE_H_