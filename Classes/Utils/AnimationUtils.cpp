#include "AnimationUtils.h"
#include "Entity/Brawler.h"

string AnimationUtils::Entities[5] = { "Shelly","Nita","Primo","Stu", "bear"};
string AnimationUtils::Types[6] = { "Top","Left","Bottom","Right", "boom", "Attack"};

/*加载动画序列*/
Animate* AnimationUtils::getAnimate(EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	/*获取英雄名和动画种类*/
	string brawlerName = Entities[entity];
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

/*运行动画*/
void AnimationUtils::runAnimate(Entity* target, EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	auto animate = AnimationUtils::getAnimate(entity, type, time, iFrameNum, loop);

	target->getSprite()->stopAllActions();
	target->getSprite()->runAction(animate->clone());
}

/*停止动画*/
void AnimationUtils::stopAnimate(Entity* target, EntityEnum entity, TypeEnum type)
{
	/*获取英雄名和动画种类*/
	string brawlerName = Entities[entity];
	string typeName = Types[type];

	/*停止动画，设置为当前方向的静止状态*/
	target->getSprite()->stopAllActions();
	target->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_" + typeName + "1.png"));
}