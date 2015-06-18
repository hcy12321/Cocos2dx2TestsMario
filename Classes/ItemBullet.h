#ifndef __ITEMBULLET_H__
#define __ITEMBULLET_H__

#include "ItemMove.h"
class ItemBoss;
class ItemBullet:public ItemMove
{
public:
	CREATE_FUNC(ItemBullet);
	bool init();
	void initBullet(ItemBoss * boss);
	void collision();
};


#endif // !__ITEMBULLET_H__
