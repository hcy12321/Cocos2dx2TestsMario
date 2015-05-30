#include "ItemMushroomAddLife.h"

ItemMushroomAddLife * ItemMushroomAddLife::create(CCDictionary* dict)
{
	ItemMushroomAddLife * ret = new ItemMushroomAddLife;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemMushroomAddLife::init(CCDictionary * dict)
{
	ItemMushroomReward::init(dict);
	_type = Item::IT_MUSHROOMADDLIFE;
	setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(IT_MUSHROOM_ADD_LIFE));

	return true;
}