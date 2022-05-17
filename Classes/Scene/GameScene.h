#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"

/*���ж�ָʾ����Ϸ������
*/

class GameScene : public cocos2d::Scene
{
private:
	std::string m_map;       //��ͼA��B��C���ݶ�
	std::string m_brawler; //Ӣ��Shelly��Primo��Nita��Stu���ݶ�

public:
	/*���������ͳ�ʼ��*/
	static cocos2d::Scene* createScene(std::string map, std::string brawler);
	virtual bool init(std::string map, std::string brawler);

	/*���� �ص�����*/
	void menuBackCallback(cocos2d::Ref* pSender);

	/*�Զ���create()*/
	static GameScene* create(std::string map, std::string brawler);
};

#endif // !__GAMESCENE_H_