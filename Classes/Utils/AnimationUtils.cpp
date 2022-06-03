#include "AnimationUtils.h"
#include "Entity/Brawler.h"

string AnimationUtils::Brawlers[4] = { "Shelly","Nita","Primo","Stu" };
string AnimationUtils::Types[4] = { "Top","Left","Bottom","Right" };

/*���ض�������*/
Animate* AnimationUtils::getAnimate(BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	/*��ȡӢ�����Ͷ�������*/
	string brawlerName = Brawlers[brawler];
	string typeName = Types[type];

	/*���ض���*/
	Vector<SpriteFrame*> frames;

	for (int i = 1; i <= iFrameNum; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_" + typeName + StringUtils::format("%d.png", i).c_str());
		frames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(frames, time / iFrameNum, loop);

	/*���ض�������*/
	return Animate::create(animation);
}

/*Ӣ�����ж���*/
void AnimationUtils::runAnimate(Brawler* targetBrawler, BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	auto animate = AnimationUtils::getAnimate(brawler, type, time, iFrameNum, loop);

	targetBrawler->getSprite()->stopAllActions();
	targetBrawler->getSprite()->runAction(animate->clone());
}

/*ֹͣ����*/
void AnimationUtils::stopAnimate(Brawler* targetBrawler, BrawlerEnum brawler, TypeEnum type)
{
	/*��ȡӢ�����Ͷ�������*/
	string brawlerName = Brawlers[brawler];
	string typeName = Types[type];

	/*ֹͣ����������Ϊ��ǰ����ľ�ֹ״̬*/
	targetBrawler->getSprite()->stopAllActions();
	targetBrawler->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_" + typeName + "1.png"));
}