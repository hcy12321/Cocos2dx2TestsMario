#ifndef __ITEMLADDERLR_H__
#define __ITEMLADDERLR_H__

#include "ItemMove.h"

class ItemLadderLR:public ItemMove
{
public:
	static ItemLadderLR * create(CCDictionary * dict);
	bool init(CCDictionary * dict);

	void move(float dt);
	void collision();

	int m_nLorR;
	int m_nladderDis;
	float m_ndis;
	bool m_bMarioOnThisLadder;
};


#endif // !__ITEMLADDERLR_H__
