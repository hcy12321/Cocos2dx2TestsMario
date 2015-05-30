#ifndef __ITEMFLYFISH_H__
#define __ITEMFLYFISH_H__

#include "Item.h"

class ItemFlyFish:public Item
{
public:
	static ItemFlyFish * create(CCDictionary* dict);
	bool init(CCDictionary * dict);

	void updateStatus();
	void move(float dt);
	void collision();

	int m_nduration;
	int m_noffsetH;
	int m_noffsetV;
	bool m_balreadyFly;

	Common::DIRECTON m_dir;

};


#endif // !__ITEMFLYFISH_H__
