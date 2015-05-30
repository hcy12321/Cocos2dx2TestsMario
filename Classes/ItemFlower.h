#ifndef __ITEMFLOWER_H__
#define __ITEMFLOWER_H__
#include "ItemMove.h"

class ItemFlower : public ItemMove
{
public:
	static ItemFlower * create(CCDictionary * dict);
	bool init(CCDictionary * dict);

	Common::DIRECTON m_dir; // UP, DOWN
	bool m_bStop; // 表现状态，花停止不动的状态
	int m_nYTop;  // 最高点
	int m_nYBottom;// 最低点

	void updateStatus();
	void move(float dt);
	void collision();

	void unsetShow(float dt);
};

#endif // !__ITEMFLOWER_H__

