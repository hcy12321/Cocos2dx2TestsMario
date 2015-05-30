#ifndef __ITEMTORTOISEROUND_H__
#define __ITEMTORTOISEROUND_H__

#include "ItemMove.h"

class ItemTortoiseRound : public ItemMove
{
public:
	static ItemTortoiseRound * create(CCDictionary* dict);
	bool init(CCDictionary * dict);

	enum{NORMAL,SLEEP,CRAZY} m_status;

	void updateStatus();
	void move(float dt);
	void collision();
	void unsetGodMode(float);

	void Recover(float);

	int m_nroundDis;
	//float m_fdis;
	int m_nleftMost;
	int m_nrightMost;
	bool m_bgod;

	Common::DIRECTON m_dir;
};
#endif // !__ITEMTORTOISEROUND_H__



