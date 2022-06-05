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
	/*UI��*/
	Size _visibleSize;
	Vec2 _origin;
	Layer* _UILayer;
	Label* _label;				//ʣ��Ӣ����
	MenuItem* _returnButton;	//���ذ�ť
	MenuItem* _emotionButton;	//���鰴ť
	Menu* _emotionMenu;			//����˵�
	Sprite* _controllerSprite;	//���������
	Sprite* _attackCenterSprite;//����������
	Sprite* _abilityCenterSprite;//���ܼ�����
	Sprite* _abilityRoundSprite; //���ܼ�����
	/*��Ҳ���*/
	Player* _player;
	Vector<AI*> _AI_Vector;
	Vector<Brawler*> _brawlerVector;
	PlayerController* _playerController;
	/*��Ƭ��ͼ����*/
	TMXTiledMap* _map;
	TMXLayer* _background;	 			//������
	TMXLayer* _wall;					//ǽ��ͼ��
	Sprite* _wallCell;					//ǽ�ڵ�Ԫ��
	TMXLayer* _collidable;				//��ײ����ͼ��
	TMXLayer* _grass;					//�ݴ�ͼ��
	Sprite* _grassCell;					//�ݴԵ�Ԫ��
	TMXLayer* _smoke;		         	//����ͼ��
	INT32   _xTileCoordMin;					//����λ��
	INT32	_xTileCoordMax;					//����λ��
	INT32	_yTileCoordMin;					//����λ��
	INT32	_yTileCoordMax;					//����λ��
	Sprite* _smokeCell;		            //���̵�Ԫ��
	TMXObjectGroup* _boxObjects;        //��������
	vector<Point> _boxPos;              //�洢ȫ������λ������
	TMXObjectGroup* _playerSpawnPoint;  //��ҳ�������������
	TMXObjectGroup* _AISpawnPoint;      //AI��������������
	
	/*��ʼ��UI�����*/
	void initLabel();			//��ǩ
	void initButton();			//��ť
	void initEmotionMenu();		//����˵�
	void initControllerSprite();//������ͼ��
	void initController();		//������
	
	/*��ʼ����ͼ��*/
	void initMap();				//��ͼ
	void initBrawler();			//Ӣ��

	/*��ʼ��Ӣ�� ��������*/
	string bindBrawler();									//��Ӣ�ۣ�����Ӣ�������ַ���
	void placeInSpawnPoint();								//������Һ�AI�ڳ�����
	void addRangeIndicator(SceneUtils::AllBrawler brawler);	//��ӷ�Χָʾ��
	void addBar(Brawler* brawler);						//���Ѫ��
	
	/*�ص�����*/
	void menuEmotionCallback(Ref *pSender);	//��ʾ����
	void menuBackCallback(Ref *pSender);	//�������˵�

public:
	static GameScene* _gameScene;
	/*���������ͳ�ʼ��*/
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	static GameScene* getGameScene() { return _gameScene; }
	void update(float dt);

	/*��Ƭ��ͼ��Ҫ�ĺ���*/
	virtual void setViewPointCenter(Point position); //���ô��ھ�ͷλ��
	Point tileCoordForPosition(Point position);	     //ת��Ϊtile����
	void setPlayerPosition(Point position);          //�������λ�ã����������ײ��
	void setGrassOpacity(Point position);            //���òݴ�͸����
	void breakWall(Point position);                  //ǽ�ڱ����дݻ�
	bool isWallTile(Point position);                  //�жϸ�λ���Ƿ�Ϊǽ��

	void setEnemyVisible(Sprite* _enemy);            //���õ����Ƿ�ɼ�
	void getBoxPosition();                           //��ȡȫ�������λ��
	void boxDie(Point position);                     //���䱻�ݻ٣�������
	void smokeMove();                                //�����ƶ�
	void smokeDamage(Point position, Brawler* brawler);//�����˺�

	/*�����ṩ�ӿ�*/
	Size getTileSize()const { return _map->getTileSize(); }
};

#endif // !__GAME_SCENE_H_