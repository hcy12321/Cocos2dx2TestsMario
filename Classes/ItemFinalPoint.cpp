#include "ItemFinalPoint.h"
#include "Mario.h"
#include "LayerGame.h"

ItemFinalPoint * ItemFinalPoint::create(CCDictionary * dict)
{
	ItemFinalPoint * ret = new ItemFinalPoint;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemFinalPoint::init(CCDictionary * dict)
{
	Item::init();
	_type = Item::IT_FINALPOINT;
	setPositionByProperty(dict);

	return true;
}

void ItemFinalPoint::collision()
{
	if (_mario->getPositionX() > getPositionX())
	{
		CCDirector::sharedDirector()->replaceScene(Common::scene(LayerGame::create((LayerGame::_idx + 1) % 8)));
	}
}