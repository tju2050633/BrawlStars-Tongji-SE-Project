#ifndef __SELECTBRAWLER_H_
#define __SELECTBRAWLER_H_

#include "cocos2d.h"

/*���ж�ָʾ��ѡ��Ӣ�۽���
���ƣ�������ɣ����Ƽ���ϸ�ڣ�
��Դ·����xy����ֵ������һ�������ݵĲ������ͺ�ֵ���ĸ��ص�������createScene()��
*/

USING_NS_CC;
using namespace std;

class SelectBrawler : public Scene
{
private:
	string _map;   //��ͼA��B��C���ݶ�

	/*��initʹ�õĳ�ʼ������*/
	void initMenu();	//��ʼ���˵�
	void initBG();		//��ʼ������

	/*ѡ��Ӣ�� �ص�����*/
	void menuShellyCallback(Ref* pSender); //ѩ��
	void menuPrimoCallback(Ref* pSender);  //����Ī
	void menuNitaCallback(Ref* pSender);   //����
	void menuSituCallback(Ref* pSender);    //˹ͼ

	/*���� �ص�����*/
	void menuBackCallback(Ref* pSender);

public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene(string map);/*��ʱ�õ�char��ʾ���ŵ�ͼ�������*/
	virtual bool init(string map);

	/*�Զ���create()*/
	static SelectBrawler* create(string map);
};

#endif // !__SELECTBRAWLER_H_