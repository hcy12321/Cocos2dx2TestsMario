#ifndef __ITEMMUSHROOMADDLIFE_H__
#define __ITEMMUSHROOMADDLIFE_H__

#include "ItemMushroomReward.h"

class ItemMushroomAddLife:public ItemMushroomReward
{
public:
	static ItemMushroomAddLife * create(CCDictionary* dict);
	bool init(CCDictionary * dict);
};
#endif // !__ITEMMUSHROOMADDLIFE_H__



