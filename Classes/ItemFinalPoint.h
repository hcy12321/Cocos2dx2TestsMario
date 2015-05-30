#ifndef __ITEMFINALPOINT__H__
#define __ITEMFINALPOINT__H__
#include "Item.h"
class ItemFinalPoint:public Item
{
public:
	static ItemFinalPoint * create(CCDictionary * dict);
	bool init(CCDictionary * dict);
	void collision();
};


#endif // !__ITEMFINALPOINT__H__
