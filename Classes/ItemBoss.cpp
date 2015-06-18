#include "ItemBoss.h"
#include "ItemBullet.h"

ItemBoss * ItemBoss::create(CCDictionary* dict)
{
	ItemBoss * ret = new ItemBoss;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemBoss::init(CCDictionary * dict)
{
	ItemMove::init();

	_type = Item::IT_BOSS;
	setPositionByProperty(dict);

	m_speedDown = m_speedAcc = 10;
	m_speed = 50;
	m_dir = Common::LEFT;

	//setPositionX(300);
	m_nleft = getPositionX() - 7 * 16;
	m_nright = getPositionX() + 2 * 16;
	m_status = NORMAL;
	m_bcanJump = true;
	m_boss = this;
	updateStatus();

	return true;
}
void ItemBoss::updateStatus()
{
	if (m_dir == Common::LEFT)
	{
		runAnimation(IT_BOSS_WALK_LEFT);
	}
	else if (m_dir == Common::RIGHT)
	{
		runAnimation(IT_BOSS_WALK_RIGHT);
	}
}

void ItemBoss::move(float dt)
{
	if (m_status == NORMAL)
	{
		// BOSS随机跳
		int randNum = CCRANDOM_0_1() * 60;
		if (randNum == 5 && m_bcanJump)
		{
			m_bcanJump = false;
			CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(ItemBoss::setAccJumpTrue));
			CCJumpBy * jump = CCJumpBy::create(.3f, ccp(0, 0), 20, 1);
			runAction(CCSequence::create(jump, callFunc, NULL));
		}
		// 随机发子弹
		randNum = CCRANDOM_0_1() * 60;

		if (randNum == 1)
		{
			// 发射子弹
			ItemBullet * bullet = ItemBullet::create();
			getMap()->addChild(bullet);
			// 根据BOSS初始化子弹
			bullet->initBullet(this);
		}

		if (m_dir == Common::LEFT)
		{
			moveLeft(dt);
			if (getPositionX() < m_nleft)
			{
				m_dir = Common::RIGHT;
				updateStatus();
			}
		}
		else
		{
			moveRight(dt);
			if (getPositionX() > m_nright)
			{
				m_dir = Common::LEFT;
				updateStatus();
			}
		}
	}
	else if (m_status == DROPPING)
	{
		moveDown(dt);
		m_speedDown += m_speedAcc;
	}
}
inline void ItemBoss::setAccJumpTrue()
{
	m_bcanJump = true;
}