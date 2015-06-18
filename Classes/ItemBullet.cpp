#include "ItemBullet.h"
#include "ItemBoss.h"
#include "Mario.h"

bool ItemBullet::init()
{
	ItemMove::init();
	// ...
	return true;
}

void ItemBullet::initBullet(ItemBoss * boss)
{
	_mario = boss->_mario;
	// 根据Boss方向设置位置
	CCRect rcBoss = boss->boundingBox();
	CCSize size = getMap()->getContentSize();
	float time = size.width / 200;
	if (boss->m_dir == Common::LEFT)
	{
		CCPoint pt = ccp(rcBoss.getMinX(), rcBoss.getMaxY());
		pt.y -= rcBoss.size.height *.2f;
		setPosition(pt);
		
		runAnimation(IT_BOSS_BULLET_LEFT);
		runAction(CCMoveBy::create(time, ccp(-size.width, 0)));
	}
	else
	{
		CCPoint pt = ccp(rcBoss.getMaxX(), rcBoss.getMaxY());
		pt.y -= rcBoss.size.height *.2f;
		setPosition(pt);
		
		runAnimation(IT_BOSS_BULLET_RIGHT);
		runAction(CCMoveBy::create(time, ccp(size.width, 0)));
	}
}

void ItemBullet::collision()
{
	if (_mario->boundingBox().intersectsRect(boundingBox()))
	{
		_mario->Die(false);
	}
	// 回收子弹
	if (getPositionX() < 0 || getPositionX() > getMap()->getContentSize().width)
	{
		removeFromParent();
	}
}