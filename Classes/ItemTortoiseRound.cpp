#include "ItemTortoiseRound.h"
#include "Mario.h"

ItemTortoiseRound * ItemTortoiseRound::create(CCDictionary* dict)
{
	ItemTortoiseRound * ret = new ItemTortoiseRound;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemTortoiseRound::init(CCDictionary * dict)
{
	ItemMove::init();
	_type = Item::IT_ITEMTORTOISEROUND;
	setPositionByProperty(dict);
	m_speed = 50;
	m_nroundDis = dict->valueForKey("roundDis")->intValue();
	m_status = NORMAL;
	m_dir = Common::LEFT;
	//m_fdis = 0;
	m_nrightMost = getPositionX();
	m_nleftMost = m_nrightMost - m_nroundDis;
	m_bgod = false;

	updateStatus();
	return true;
}

void ItemTortoiseRound::updateStatus()
{
	stopAllActions();
	if (m_status == NORMAL)
	{
		CCAnimation * animation = NULL;
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
	else if (m_status == CRAZY)
	{
		m_speed = 200;
		m_dir = _mario->_dirFace;
		m_bgod = true;
		scheduleOnce(schedule_selector(ItemTortoiseRound::unsetGodMode), 0.2f);
	}
	else if (m_status == SLEEP)
	{
		CCAnimation * animation = NULL;
		animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_TORTOISE_DEAD);
		CCAnimate * animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));

		// 过一段时间恢复
		scheduleOnce(schedule_selector(ItemTortoiseRound::Recover), 10);
		// 不接受碰撞一段时间
		m_bgod = true;
		scheduleOnce(schedule_selector(ItemTortoiseRound::unsetGodMode), 0.2f);
		_mario->bounce();
	}
}

void ItemTortoiseRound::unsetGodMode(float)
{
	m_bgod = false;
}

void ItemTortoiseRound::move(float dt)
{
	if (!isLeftInWindow()) return;

	if (isFarAwayFromMario())
	{
		removeFromParent();
		return;
	}
		

	if (m_status == SLEEP)
		return;
	if (m_status == NORMAL)
	{
		if (m_dir == Common::LEFT)
		{
			Common::moveNode(this, ccp(-dt * m_speed, 0));
			if (getPositionX() <= m_nleftMost)
			{
				m_dir = Common::RIGHT;
				updateStatus();
			}
		}
		else
		{
			Common::moveNode(this, ccp(dt * m_speed, 0));
			if (getPositionX() >= m_nrightMost)
			{
				m_dir = Common::LEFT;
				updateStatus();
			}
		}
	}
	else if (m_status == CRAZY)
	{
		if (m_dir == Common::LEFT)
		{
			if (canMoveLeft(dt))
				Common::moveNode(this, ccp(-dt * m_speed, 0));
			else
				m_dir = Common::RIGHT;
		}
		else
		{
			if (canMoveRight(dt))
				Common::moveNode(this, ccp(dt * m_speed, 0));
			else
				m_dir = Common::LEFT;
		}
	}

	if (canMoveDown(dt))
		moveDown(dt);
	
}

void ItemTortoiseRound::Recover(float)
{
	m_status = NORMAL;
	updateStatus();
}

void ItemTortoiseRound::collision()
{

	if (m_bgod) return;
	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = this->boundingBox();

	// 判断碰撞检测
	if (rcMario.intersectsRect(rcItem))
	{
		if (m_status == NORMAL)
		{
			if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
			{
				m_status = SLEEP;
				updateStatus();
			}
			else
			{

			}
		}
		else if (m_status == SLEEP)
		{
			unschedule(schedule_selector(ItemTortoiseRound::Recover));
			m_status = CRAZY;
			updateStatus();
		}
		else if (m_status == CRAZY)
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

	}
}
