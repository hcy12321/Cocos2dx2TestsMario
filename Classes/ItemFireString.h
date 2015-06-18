#ifndef __ITEMFIRESTRING_H__
#define __ITEMFIRESTRING_H__

#include "Item.h"

class ItemFireString:public Item
{
public:
	static ItemFireString * create(CCDictionary* dict);
	bool init(CCDictionary * dict);

	void collision();

};


#endif // !__ITEMFIRESTRING_H__
