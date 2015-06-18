#include "ItemBridgeStartPos.h"
#include "Mario.h"
#include "ItemBoss.h"

ItemBridgeStartPos * ItemBridgeStartPos::create(CCDictionary* dict)
{
	ItemBridgeStartPos * ret = new ItemBridgeStartPos;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemBridgeStartPos::init(CCDictionary * dict)
{
	Item::init();

	_type = Item::IT_BRIDGE_POS;

	setPositionByProperty(dict);

	setContentSize(CCSizeMake(16, 16));
	m_bridge = this;
	return true;
}

void ItemBridgeStartPos::collision()
{
	//if (boundingBox().intersectsRect(_mario->boundingBox()))
	//{
	//	// ฒ๐วล
	//	ItemBoss * boss = (ItemBoss *)m_boss;
	//	boss->m_status = ItemBoss::DROPPING;

	//	CCTMXLayer * land = getMap()->layerNamed("land");
	//	CCPoint ptTile = Common::Point2Tile(getMap(), getPosition());
	//	for (int i = 0; i < 13; ++i)
	//	{
	//		land->setTileGID(0, ccp(ptTile.x + i, ptTile.y));
	//	}
	//	
	//}
}