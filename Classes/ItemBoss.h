#ifndef __ITEMBOSS_H__
#define __ITEMBOSS_H__

#include "ItemMove.h"

class ItemBoss:public ItemMove
{
public:
	static ItemBoss * create(CCDictionary* dict);
	bool init(CCDictionary * dict);

	void updateStatus();
	void move(float dt);
	void setAccJumpTrue();

	Common::DIRECTON m_dir;

	int m_nleft;
	int m_nright;
	bool m_bcanJump;
	enum{NORMAL, DROPPING} m_status;
};


#endif // !__ITEMBOSS_H__
