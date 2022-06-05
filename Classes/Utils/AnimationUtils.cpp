#include "AnimationUtils.h"
#include "Entity/Brawler.h"

string AnimationUtils::Entities[5] = { "Shelly","Nita","Primo","Stu", "bear"};
string AnimationUtils::Types[6] = { "Top","Left","Bottom","Right", "boom", "Attack"};

/*���ض�������*/
Animate* AnimationUtils::getAnimate(EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	/*��ȡӢ�����Ͷ�������*/
	string brawlerName = Entities[entity];
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

/*���ж���*/
void AnimationUtils::runAnimate(Entity* target, EntityEnum entity, TypeEnum type, float time, INT32 iFrameNum, INT32 loop)
{
	auto animate = AnimationUtils::getAnimate(entity, type, time, iFrameNum, loop);

	target->getSprite()->stopAllActions();
	target->getSprite()->runAction(animate->clone());
}

/*ֹͣ����*/
void AnimationUtils::stopAnimate(Entity* target, EntityEnum entity, TypeEnum type)
{
	/*��ȡӢ�����Ͷ�������*/
	string brawlerName = Entities[entity];
	string typeName = Types[type];

	/*ֹͣ����������Ϊ��ǰ����ľ�ֹ״̬*/
	target->getSprite()->stopAllActions();
	target->getSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(brawlerName + "_" + typeName + "1.png"));
}