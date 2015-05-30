#include "ItemTortoiseFly.h"

ItemTortoiseFly * ItemTortoiseFly::create(CCDictionary* dict)
{
	ItemTortoiseFly * ret = new ItemTortoiseFly;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemTortoiseFly::init(CCDictionary * dict)
{
	ItemMove::init();

	_type = Item::IT_TORTOISEFLY;

	setPositionByProperty(dict);

	m_status = NORMAL;
	m_dir = Common::LEFT;
	return true;
}

void ItemTortoiseFly::updateStatus()
{

}
void ItemTortoiseFly::move(float dt)
{

}
void ItemTortoiseFly::collision()
{

}