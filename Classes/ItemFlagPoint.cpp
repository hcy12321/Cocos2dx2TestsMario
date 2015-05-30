#include "ItemFlagPoint.h"
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
	}
}