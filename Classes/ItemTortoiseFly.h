#ifndef __TORTOISEFLY_H__
#define __TORTOISEFLY_H__

#include "ItemMove.h"

class ItemTortoiseFly :public ItemMove
{
public:
	static ItemTortoiseFly * create(CCDictionary* dict);
	bool init(CCDictionary * dict);
	void updateStatus();
	void move(float dt);
	void collision();
	void Recover(float dt);

	/* ״̬ */
	enum {NORMAL, DROPPING, ONLAND, SLEEP, CRAZY} m_status;
	Common::DIRECTON m_dir;
	int m_nflyDis;
	int m_nleft;
	int m_nright;
	
};


#endif // !__TORTOISEFLY_H__
