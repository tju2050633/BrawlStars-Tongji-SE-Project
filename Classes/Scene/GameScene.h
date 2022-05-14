#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"

/*���ж�ָʾ����Ϸ������
*/

class GameScene : public cocos2d::Scene
{
private:
    char m_map;       //��ͼA��B��C���ݶ�
    String m_brawler; //Ӣ��Shelly��Primo��Nita��Stu���ݶ�

public:
    /*���������ͳ�ʼ��*/
    static cocos2d::Scene* createScene(char map, String brawler);
    virtual bool init(char map, String brawler);
    
};

#endif //__GAMESCENE_H_