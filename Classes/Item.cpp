#include "Item.h"
#include "ItemMushroom.h"
#include "ItemTortoise.h"
#include "ItemFlower.h"
#include "Mario.h"
#include "ItemMushroomReward.h"
#include "ItemMushroomAddLife.h"
#include "ItemFlagPoint.h"
#include "ItemFinalPoint.h"
#include "ItemLadderLR.h"
#include "ItemFlyFish.h"
#include "ItemTortoiseRound.h"
#include "ItemTortoiseFly.h"
#include "ItemLadderUD.h"
#include "ItemFireString.h"
#include "ItemBoss.h"
#include "ItemBridgeStartPos.h"

CCArray * Item::m_arrItemReward = NULL;
Item * Item::_Flag;
Item * Item::m_boss;
Item * Item::m_bridge;

Item::~Item()
{
}
bool Item::init()
{
	CCSprite::init();
	setZOrder(100);
	scheduleUpdate();
	m_actionForStop = NULL;
	return true;
}
Item * Item::create(CCDictionary * dict)
{

	const CCString * type = dict->valueForKey("type");

	if (type->m_sString == "mushroom")
		return ItemMushroom::create(dict);
	else if (type->m_sString == "tortoise")
		return ItemTortoise::create(dict);
	else if (type->m_sString == "flower")
		return ItemFlower::create(dict);
	else if (type->m_sString == "MushroomReward")
		return ItemMushroomReward::create(dict);
	else if (type->m_sString == "MushroomAddLife")
		return ItemMushroomAddLife::create(dict);
	else if (type->m_sString == "flagpoint")
		return ItemFlagPoint::create(dict);
	else if (type->m_sString == "finalpoint")
		return ItemFinalPoint::create(dict);
	else if (type->m_sString == "ladderLR")
		return ItemLadderLR::create(dict);
	else if (type->m_sString == "flyfish")
		return ItemFlyFish::create(dict);
	else if (type->m_sString == "tortoise_round")
		return ItemTortoiseRound::create(dict);
	else if (type->m_sString == "tortoise_fly")
		return ItemTortoiseFly::create(dict);
	else if (type->m_sString == "ladderUD")
		return ItemLadderUD::create(dict);
	else if (type->m_sString == "fire_string")
		return ItemFireString::create(dict);
	else if (type->m_sString == "boss")
		return ItemBoss::create(dict);
	else if (type->m_sString == "bridgestartpos")
		return ItemBridgeStartPos::create(dict);
	return NULL;
}
void Item::setPositionByProperty(CCDictionary * dict)
{
	const CCString * x = dict->valueForKey("x");
	const CCString * y = dict->valueForKey("y");
	setPosition(ccp(x->intValue(), y->intValue() - 16));
	setAnchorPoint(ccp(0, 0));
}

CCTMXTiledMap * Item::getMap()
{
	return (CCTMXTiledMap *)getParent();
}

bool Item::isLeftInWindow()
{
	//CCPoint ptInMap = getPosition();
	CCRect rcItem = boundingBox();
	CCPoint ptInMap = ccp(rcItem.getMinX(), rcItem.getMinY());
	CCTMXTiledMap * map = getMap();
	CCPoint ptInWorld = map->convertToWorldSpace(ptInMap);
	if (ptInWorld.x <= winSize.width)
	{
		return true;
	}
	return false;
}

bool Item::isFarAwayFromMario()
{
	CCRect rcItem = this->boundingBox();
	CCRect rcMario = _mario->boundingBox();
	if (rcMario.getMinX() - rcItem.getMaxX() > winSize.width)
		return true;
	return false;
}

void Item::move(float dt)
{

}
void Item::collision(){}
void Item::wakeup(){}
void Item::update(float dt)
{
	move(dt);
	collision();
}

inline void Item::runAnimation(const char * name)
{
	//stopAllActions();
	if (m_actionForStop != NULL)
	{
		stopAction(m_actionForStop);
	}
	// 保存执行动画，以便下次停止
	runAction(m_actionForStop = Common::GetAnimateForeverActionByCacheName(name));
}