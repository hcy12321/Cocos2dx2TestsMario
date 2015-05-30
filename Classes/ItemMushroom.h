#ifndef __ITEMMUSHROOM_H__
#define __ITEMMUSHROOM_H__

#include "ItemMove.h"

class ItemMushroom: public ItemMove
{
public:
	static ItemMushroom * create(CCDictionary * dict);

	void move(float dt);
	void moveDown(float dt);
	void collision();

	bool init(CCDictionary * dict);
	bool canMove(float dt);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);
	
	bool m_bIsDead;
	Common::DIRECTON m_dir;
};



#endif // !__ITEMMUSHROOM_H__

