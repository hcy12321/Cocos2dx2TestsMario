#ifndef __ITEMTORTOISE_H__
#define __ITEMTORTOISE_H__
#include "ItemMove.h"
class ItemTortoise:public ItemMove
{
public:
	static ItemTortoise * create(CCDictionary* dict);
	bool init(CCDictionary * dict);

	void move(float dt);
	void moveDown(float dt);
	void collision();

	bool canMove(float dt);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);

	void unsetGodMode(float dt);
	void revival(float dt);

	bool _isCrazy; //
	bool _isGod;	// ��mario�ȵ�ʱ��Ҫһ��ʱ����޵�״̬
	bool _isSleep; // ��mario����һ�Ρ�����һ��ʱ�䣬Ҫ����
	bool m_bIsDead;
	Common::DIRECTON m_dir;
};
#endif // !__ITEMTORTOISE_H__



