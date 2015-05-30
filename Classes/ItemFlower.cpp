#include "ItemFlower.h"
#include "Mario.h"

ItemFlower * ItemFlower::create(CCDictionary * dict)
{
	ItemFlower * ret = new ItemFlower;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemFlower::init(CCDictionary * dict)
{
	ItemMove::init();

	// 播放动画
	CCAnimate * animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(IT_FLOWER_SHOW));
	runAction(CCRepeatForever::create(animate));

	setZOrder(0);
	_type = Item::IT_FLOWER;
	setPositionByProperty(dict);
	Common::moveNode(this, ccp(-8, 0));
	m_dir = Common::UP; // UP,DOWN
	m_bStop = true;// 表现状态
	m_nYTop = getPositionY();
	m_nYBottom = m_nYTop - 32;
//	m_nYBottom = Common::Tile2PointLB(this->getMap(), ccp(0, 11)).y;
	m_speed = 50;

	// 更新显示
	updateStatus();
	return true;
}

void ItemFlower::updateStatus()
{
	if (m_bStop)
	{
		// 启动定时器取消show
		scheduleOnce(schedule_selector(ItemFlower::unsetShow), 2);
	}
}

void ItemFlower::move(float dt)
{
	if (m_bStop) return;
	if (m_dir == Common::DOWN)
	{
		Common::moveNode(this, ccp(0, -dt * m_speed));
		// 如果向下移动到了某个地方（bottom）,改变方向
		if (getPositionY() <= m_nYBottom)
		{
			// 微调
			this->setPositionY(m_nYBottom);
			m_bStop = true;
			updateStatus();
			//m_dir = Common::UP;
			
		}
	}
	else
	{
		CCRect rcItem = this->boundingBox();
		rcItem.size.height = rcItem.size.height + m_nYTop - m_nYBottom;
		CCRect rcMario = _mario->boundingBox();
		// 如果mario踩在花头顶，花不能动
		if (rcItem.intersectsRect(rcMario))
		{
			return;
		}

		Common::moveNode(this, ccp(0, dt * m_speed));
		// 如果向上移动到了某个地方，就改变状态
		if (getPositionY() >= m_nYTop)
		{
			// 微调
			this->setPositionY(m_nYTop);
			m_bStop = true;
			updateStatus();
		}
	}
}

inline void ItemFlower::unsetShow(float dt)
{
	m_bStop = false;
	m_dir == Common::DOWN ? m_dir = Common::UP : m_dir = Common::DOWN;
}

void ItemFlower::collision()
{
	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = boundingBox();
	if (rcMario.intersectsRect(rcItem))
	{
		_mario->Die(false);
	}
}