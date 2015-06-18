#ifndef __ITEMLADDERUD_H__
#define __ITEMLADDERUD_H__

#include "ItemMove.h"

class ItemLadderUD:public ItemMove
{
public:
	static ItemLadderUD *create(CCDictionary* dict);
	bool init(CCDictionary * dict);
	void move(float dt);
	void collision();

	int m_nUorD;
	int m_nladderDis;
	float m_fdis;
	bool m_bmarioOnThisLadder;

};


#endif // !__ITEMLADDERUD_H__
