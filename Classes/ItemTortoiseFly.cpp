#include "ItemTortoiseFly.h"
#include "Mario.h"

ItemTortoiseFly * ItemTortoiseFly::create(CCDictionary* dict)
{
	ItemTortoiseFly * ret = new ItemTortoiseFly;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemTortoiseFly::init(CCDictionary * dict)
{
	ItemMove::init();

	_type = Item::IT_TORTOISEFLY;

	setPositionByProperty(dict);

	m_status = NORMAL;
	m_dir = Common::LEFT;
	m_nflyDis = dict->valueForKey("flyDis")->intValue();
	m_nright = getPositionX();
	m_nleft = m_nright - m_nflyDis;
	m_speed = 50;
	m_speedDown = m_speedAcc = 10;
	updateStatus();
	return true;
}

void ItemTortoiseFly::updateStatus()
{
	CCAnimation * animation = NULL;
	if (m_status == NORMAL)
	{
		stopAllActions();
		if (m_dir == Common::LEFT)
		{
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_TORTOISE_FLY_LEFT_ANIMATE_NAME);
		}
		else
		{
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_TORTOISE_FLY_RIGHT_ANIMATE_NAME);
		}
		CCAnimate * animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else if (m_status == DROPPING)
	{
		stopAllActions();
		_mario->bounce();
		if (m_dir == Common::LEFT)
		{
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_TORTOISE_MOVING_LEFT_ANIMATE_NAME);
		}
		else
		{
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_TORTOISE_MOVING_RIGHT_ANIMATE_NAME);
		}
		CCAnimate * animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else if (m_status == ONLAND)
	{
		// ...
	}
	else if (m_status == SLEEP)
	{
		stopAllActions();
		animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_TORTOISE_DEAD);
		CCAnimate * animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
		// 过一段时间恢复
		scheduleOnce(schedule_selector(ItemTortoiseFly::Recover), 10);
		setGodMode(0.2f);
		_mario->bounce();
	}
	else if (m_status == CRAZY)
	{
		// 过一段时间恢复
		setGodMode(0.2f);
		_mario->bounce();
		unschedule(schedule_selector(ItemTortoiseFly::Recover));
		m_speed = 200;
	}
}

void ItemTortoiseFly::Recover(float)
{
	m_status = NORMAL;
	updateStatus();
}

void ItemTortoiseFly::move(float dt)
{
	if (!isLeftInWindow()) return;

	if (isFarAwayFromMario())
	{
		removeFromParent();
		return;
	}
	if (m_status == NORMAL)
	{
		if (m_dir == Common::LEFT)
		{
			moveLeft(dt);
			if (getPositionX() <= m_nleft)
			{
				m_dir = Common::RIGHT;
				updateStatus();
			}
		}
		else
		{
			moveRight(dt);
			if (getPositionX() >= m_nright)
			{
				m_dir = Common::LEFT;
				updateStatus();
			}
		}
	}
	else if (m_status == DROPPING)
	{
		if (canMoveDown(dt))
		{
			moveDown(dt);
			m_speedDown += m_speedAcc;
		}
		else
		{
			m_speedDown = m_speedAcc;
			m_status = ONLAND;
			updateStatus();
		}
	}
	else if (m_status == ONLAND || m_status == CRAZY)
	{
		if (canMoveDown(dt))
		{
			moveDown(dt);
			m_speedDown += m_speedAcc;
		}
		else
		{
			m_speedDown = m_speedAcc;
		}
		// ...
		if (m_dir == Common::LEFT)
		{
			if (canMoveLeft(dt))
			{
				moveLeft(dt);
			}
			else
			{
				m_dir = Common::RIGHT;
				updateStatus();
			}
		}
		else
		{
			if (canMoveRight(dt))
			{
				moveRight(dt);
			}
			else
			{
				m_dir = Common::LEFT;
				updateStatus();
			}
		}
	}
}
void ItemTortoiseFly::collision()
{
	if (m_bgodMode) return;
	CCRect rcItem = boundingBox();
	CCRect rcMario = _mario->boundingBox();
	if (rcItem.intersectsRect(rcMario))
	{
		if (m_status == NORMAL)
		{
			if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
			{
				m_status = DROPPING;
				updateStatus();
			}
			else
			{
				_mario->Die(false);
			}
		}
		else if (m_status == DROPPING)
		{
			// 出现问题
			CCLog("should be no collision");
		}
		else if (m_status == ONLAND)
		{
			if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
			{
				m_status = SLEEP;
				updateStatus();
			}
			else
			{
				_mario->Die(false);
			}
		}
		else if (m_status == SLEEP)
		{
			m_status = CRAZY;
			updateStatus();
		}

	}
}