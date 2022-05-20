#ifndef __SELECTBRAWLER_H_
#define __SELECTBRAWLER_H_

#include "cocos2d.h"
#include "SceneManager.h"

/*���ж�ָʾ��ѡ��Ӣ�۽���
���ƣ�������ɣ����Ƽ���ϸ�ڣ�
��Դ·����xy����ֵ������һ�������ݵĲ������ͺ�ֵ���ĸ��ص�������createScene()��
*/

USING_NS_CC;
using namespace std;

class SelectBrawler : public Scene
{
private:
	/*��initʹ�õĳ�ʼ������*/
	void initMenu(); //��ʼ���˵�

	/*ѡ��Ӣ�� �ص�����*/
	void menuShellyCallback(Ref *pSender); //ѩ��
	void menuPrimoCallback(Ref *pSender);  //����Ī
	void menuNitaCallback(Ref *pSender);   //����
	void menuStuCallback(Ref *pSender);	   //˹ͼ

	/*���� �ص�����*/
	void menuBackCallback(Ref *pSender);

public:
	/*���������ͳ�ʼ��*/
	static Scene *createScene(); /*��ʱ�õ�char��ʾ���ŵ�ͼ�������*/
	virtual bool init();

	/*�Զ�����create()�ĺ�*/
	CREATE_FUNC(SelectBrawler);
};

#endif // !__SELECTBRAWLER_H_