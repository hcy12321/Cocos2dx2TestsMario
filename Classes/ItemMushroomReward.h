#ifndef __ITEMMUSHROOMREWARD_H__
#define __ITEMMUSHROOMREWARD_H__

#include "ItemMove.h"

class ItemMushroomReward:public ItemMove
{
public:
	static ItemMushroomReward * create(CCDictionary * dict);
	bool init(CCDictionary * dict);

	void wakeup();
	void updateStatus();
	void afterGrow();

	void move(float dt);
	bool canMove(float dt);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);
	void moveDown(float dt);
	void collision();

	enum { SLEEP, GROW, MOVE } m_status;
	Common::DIRECTON m_dir;

};

#endif // !__ITEMMUSHROOMREWARD_H__


