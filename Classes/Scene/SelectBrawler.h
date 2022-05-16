#ifndef __SELECTBRAWLER_H_
#define __SELECTBRAWLER_H_

#include "cocos2d.h"

/*���ж�ָʾ��ѡ��Ӣ�۽���
���ƣ�������ɣ����Ƽ���ϸ�ڣ�
��Դ·����xy����ֵ������һ�������ݵĲ������ͺ�ֵ���ĸ��ص�������createScene()��
*/

class SelectBrawler : public cocos2d::Scene
{
private:
	std::string m_map;   //��ͼA��B��C���ݶ�

public:
	/*���������ͳ�ʼ��*/
	static cocos2d::Scene* createScene(std::string map);/*��ʱ�õ�char��ʾ���ŵ�ͼ�������*/
	virtual bool init(std::string map);

	/*ѡ��Ӣ�� �ص�����*/
	void menuShellyCallback(cocos2d::Ref* pSender); //ѩ��
	void menuPrimoCallback(cocos2d::Ref* pSender);  //����Ī
	void menuNitaCallback(cocos2d::Ref* pSender);   //����
	void menuSituCallback(cocos2d::Ref* pSender);    //˹ͼ

	/*���� �ص�����*/
	void menuBackCallback(cocos2d::Ref* pSender);

	/*�Զ���create()*/
	static SelectBrawler* create(std::string map);
};

#endif //__SELECTBRAWLER_H_