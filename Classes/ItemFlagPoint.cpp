#include "ItemFlagPoint.h"
#include "ItemBoss.h"
#include "Mario.h"

ItemFlagPoint * ItemFlagPoint::create(CCDictionary* dict)
{
	ItemFlagPoint * ret = new ItemFlagPoint;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemFlagPoint::init(CCDictionary * dict)
{
	Item::init();
	_Flag = this;
	_type = Item::IT_FLAGPOINT;

	setPositionByProperty(dict);

	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("flag.png");
	setTexture(texture);
	setTextureRect(CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));

	Common::moveNode(this, ccp(-texture->getContentSize().width / 2, 0));
	_bCollisionWithMario = false;

	return true;
}
void ItemFlagPoint::collision()
{
	if (_bCollisionWithMario)return;
	if (_mario->boundingBox().intersectsRect(boundingBox()))
	{
		_bCollisionWithMario = true;
		_mario->autoRun2();

		if (boundingBox().intersectsRect(_mario->boundingBox()))
		{
			// ฒ๐วล
			if (m_bridge != NULL)
			{
				ItemBoss * boss = (ItemBoss *)m_boss;
				boss->m_status = ItemBoss::DROPPING;

				CCTMXLayer * land = getMap()->layerNamed("land");
				CCPoint ptTile = Common::Point2Tile(getMap(), m_bridge->getPosition());
				for (int i = 0; i < 13; ++i)
				{
					land->setTileGID(0, ccp(ptTile.x + i, ptTile.y));
				}
			}
		}
	}
}