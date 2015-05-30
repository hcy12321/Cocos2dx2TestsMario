#ifndef __ITEMFLOWER_H__
#define __ITEMFLOWER_H__
#include "ItemMove.h"

class ItemFlower : public ItemMove
{
public:
	static ItemFlower * create(CCDictionary * dict);
	bool init(CCDictionary * dict);

	Common::DIRECTON m_dir; // UP, DOWN
	bool m_bStop; // ����״̬����ֹͣ������״̬
	int m_nYTop;  // ��ߵ�
	int m_nYBottom;// ��͵�

	void updateStatus();
	void move(float dt);
	void collision();

	void unsetShow(float dt);
};

#endif // !__ITEMFLOWER_H__

