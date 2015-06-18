#ifndef __ITEMMOVE_H__
#define __ITEMMOVE_H__

#include "Item.h"

class ItemMove:public Item
{
public:
	bool init();

	virtual bool canMoveLeft(float dt);
	virtual bool canMoveRight(float dt);
	virtual bool canMoveDown(float dt);

	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveDown(float dt);

	void setGodMode(int time);
	void unsetGodMode(float dt);

	int m_speedDown;
	int m_speed;
	int m_speedAcc;
	bool m_bgodMode;
};



#endif // !__ITEMMOVE_H__

