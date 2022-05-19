#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"
#include "SceneManager.h"

/*���ж�ָʾ����Ϸ������
*/

class GameScene : public cocos2d::Scene
{
private:
	std::string m_map;       //��ͼA��B��C���ݶ�
	std::string m_brawler; //Ӣ��Shelly��Primo��Nita��Stu���ݶ�

public:
	/*���������ͳ�ʼ��*/
	static cocos2d::Scene* createScene(SceneManager::AllMap map, SceneManager::AllBrawler brawler);
	virtual bool init(SceneManager::AllMap map, SceneManager::AllBrawler brawler);

	/*���� �ص�����*/
	void menuBackCallback(cocos2d::Ref* pSender);

	/*�Զ���create()*/
	static GameScene* create(SceneManager::AllMap map, SceneManager::AllBrawler brawler);
};

#endif // !__GAMESCENE_H_