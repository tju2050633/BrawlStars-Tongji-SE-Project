#ifndef __SELECT_BRAWLER_H_
#define __SELECT_BRAWLER_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SelectBrawler : public Layer
{
private:
	/*��initʹ�õĳ�ʼ������*/
	void initMenu(); //��ʼ���˵�

	/*ѡ��Ӣ�� �ص�����*/
	void menuShellyCallback(Ref* pSender); //ѩ��
	void menuPrimoCallback(Ref* pSender);  //����Ī
	void menuNitaCallback(Ref* pSender);   //����
	void menuStuCallback(Ref* pSender);	   //˹ͼ

	/*���� �ص�����*/
	void menuBackCallback(Ref* pSender);

public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectBrawler);
};

#endif // !__SELECT_BRAWLER_H_