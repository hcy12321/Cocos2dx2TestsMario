#ifndef __ITEMBRIDGESTARTPOS_H__
#define __ITEMBRIDGESTARTPOS_H__

#include "Item.h"

class ItemBridgeStartPos:public Item
{
public:
	static ItemBridgeStartPos * create(CCDictionary* dict);
	bool init(CCDictionary * dict);

	void collision();

};


#endif // !__ITEMBRIDGESTARTPOS_H__
