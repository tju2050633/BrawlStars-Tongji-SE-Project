#ifndef __ROOM_H_
#define __ROOM_H_

#include "cocos2d.h"
#include "Utils/SceneUtils.h"

USING_NS_CC;

class Room : public Layer
{
private:
	/*�˵���ʼ��*/
	void initMenu();

	/*��ǩ��ʼ��*/
	void initLabel();

	/*���Ӣ��ͷ��*/
	void addPortrait(SceneUtils::AllBrawler brawler);

	Vector<Label*> _labels;

	/*��ʼ �ص�����*/
	void menuStartCallback(Ref* pSender);

	/*���Shelly �ص�����*/
	void menuAddShellyCallback(Ref* pSender);

	/*���Nita �ص�����*/
	void menuAddNitaCallback(Ref* pSender);

	/*���Primo �ص�����*/
	void menuAddPrimoCallback(Ref* pSender);

	/*���Stu �ص�����*/
	void menuAddStuCallback(Ref* pSender);

	/*���� �ص�����*/
	void menuBackCallback(Ref* pSender);

public:
	/*���������ͳ�ʼ��*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Room);
};

#endif // !__ROOM_H_