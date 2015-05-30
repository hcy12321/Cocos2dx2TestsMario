#ifndef __ITEMFLAGPOINT_H__
#define __ITEMFLAGPOINT_H__

#include "Item.h"

class ItemFlagPoint:public Item
{
public:
	static ItemFlagPoint * create(CCDictionary* dict);
	bool init(CCDictionary * dict);

	void collision();
	bool _bCollisionWithMario;

};
#endif // !__ITEMFLAGPOINT_H__


