#include "AnimationUtils.h"
#include "Entity/Brawler.h"

string AnimationUtils::Brawlers[4] = { "Shelly","Nita","Primo","Stu" };
string AnimationUtils::Types[4] = { "Top","Left","Bottom","Right" };

/*加载动画序列*/
Animate* AnimationUtils::getAnimate(BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	/*获取英雄名和动画种类*/
	string brawlerName = Brawlers[brawler];
	string typeName = Types[type];

	/*加载动画*/
	Vector<SpriteFrame*> frames;

	for (int i = 1; i <= iFrameNum; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_" + typeName + StringUtils::format("%d.png", i).c_str());
		frames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(frames, time / iFrameNum, loop);

	/*返回动画序列*/
	return Animate::create(animation);
}

/*英雄运行动画*/
void AnimationUtils::runAnimate(Brawler* targetBrawler, BrawlerEnum brawler, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	auto animate = AnimationUtils::getAnimate(brawler, type, time, iFrameNum, loop);

	targetBrawler->getSprite()->stopAllActions();
	targetBrawler->getSprite()->runAction(animate->clone());
}

/*停止动画*/
void AnimationUtils::stopAnimate(Brawler* targetBrawler, BrawlerEnum brawler, TypeEnum type)
{
	/*获取英雄名和动画种类*/
	string brawlerName = Brawlers[brawler];
	string typeName = Types[type];

	/*停止动画，设置为当前方向的静止状态*/
	targetBrawler->getSprite()->stopAllActions();
	targetBrawler->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_" + typeName + "1.png"));
}