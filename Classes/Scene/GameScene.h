#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_

#include "cocos2d.h"
#include <string>
#include <vector>
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
	Sprite* _attackCenterSprite;
	Sprite* _abilityCenterSprite;
	Sprite* _abilityRoundSprite;
	/*��Ҳ���*/
	Player* _player;
	PlayerController* _playerController;
	/*��Ƭ��ͼ����*/
	TMXTiledMap* _map;
	TMXLayer* _background;	          	//������
	TMXLayer* _wall;		           	//ǽ��ͼ��
	Sprite* _wallCell;		         	//ǽ�ڵ�Ԫ��
	TMXLayer* _collidable;		        //��ײ����ͼ��
	TMXLayer* _grass;		           	//�ݴ�ͼ��
	Sprite* _grassCell;			        //�ݴԵ�Ԫ��
	Sprite* _boxCell;		           	//���䵥Ԫ��
	TMXLayer* _smoke;		         	//����ͼ��
	Sprite* _smokeCell;		            //���̵�Ԫ��
	TMXLayer* _box;			            //����ͼ��
	TMXObjectGroup* _boxObjects;        //��������
	vector<Point> _boxPos;              //�洢ȫ������λ������
	TMXObjectGroup* _playerSpawnPoint;  //��ҳ�������������
	TMXObjectGroup* _AISpawnPoint;      //AI��������������
	
	/*UI�����*/
	void initLabel();			//��ǩ
	void initButton();			//��ť
	void initControllerSprite();//������ͼ��
	
	/*��ʼ��*/
	void initMap();				//��ͼ
	void initBrawler();			//Ӣ��
	void initAI();              //AI
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
	Point tileCoordForPosition(Point position);	     //ת��Ϊtile����
	void setPlayerPosition(Point position);          //�������λ�ã����������ײ��
	void setGrassOpacity(Point position);            //���òݴ�͸����
	void breakWall(Point position);                  //ǽ�ڱ����дݻ�
	void setEnemyVisible(Sprite *_enemy);            //���õ����Ƿ�ɼ�
	void getBoxPosition();                           //��ȡȫ�������λ��
	void boxDie(Point position);                     //���䱻�ݻ٣�������
	void smokeMove();                                //�����ƶ�
	void smokeDamage(Point position);                //�����˺�
};

#endif // !__GAME_SCENE_H_