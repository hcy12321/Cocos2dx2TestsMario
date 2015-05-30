#include "ItemTortoise.h"
#include "Mario.h"

ItemTortoise * ItemTortoise::create(CCDictionary * dict)
{
	ItemTortoise * ret = new ItemTortoise;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemTortoise::init(CCDictionary * dict)
{
	ItemMove::init();
	_type = Item::IT_TORTOISE;
	// 设置位置
	setPositionByProperty(dict);
	// 设置图片
	//setDisplayFrameWithAnimationName("MushroomMoving", 0);

	m_dir = Common::LEFT;
	m_speed= 50;
	m_speedDown = m_speedAcc = 10;
	m_bIsDead = false;
	_isGod = false;
	_isSleep = false;
	_isCrazy = false;
	// 加载动画
	this->runAction(Common::GetAnimateForeverActionByCacheName(IT_TORTOISE_MOVING_LEFT_ANIMATE_NAME));
	return true;
}

bool ItemTortoise::canMoveLeft(float dt)
{
	// 跑到地图外
	CCRect rcItem = boundingBox();
	CCPoint ptItem = ccp(rcItem.getMinX(), rcItem.getMinY());
	CCTMXTiledMap * map = getMap();
	if (map == NULL)
	{
		return false;
	}
	CCPoint ptItemInWorld = map->convertToWorldSpace(ptItem);
	if (ptItemInWorld.x - dt* m_speed < -rcItem.size.width)
		return false;

	// 碰到障碍物
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMinX() - dt*m_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMinX() - dt*m_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMinX() - dt*m_speed, rcItem.getMaxY());
	// 坐标转换，讲pt转化为地图格子坐标，然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height || pt[i].y <= 0)
			continue;
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头、地板
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				//变化方向
				m_dir = Common::RIGHT;

				if (!_isCrazy)
				{
					stopAllActions();
					this->runAction(Common::GetAnimateForeverActionByCacheName(IT_TORTOISE_MOVING_RIGHT_ANIMATE_NAME));
				}
				return false;
			}
		}
	}
	return true;
}

bool ItemTortoise::canMoveRight(float dt)
{
	CCRect rcItem = boundingBox();
	CCTMXTiledMap * map = getMap();
	if (map == NULL)
	{
		return false;
	}
	// 碰到障碍物
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMaxX() + dt*m_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMaxX() + dt*m_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMaxX() + dt*m_speed, rcItem.getMaxY());
	// 坐标转换，讲pt转化为地图格子坐标，然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height || pt[i].y <= 0)
			continue;
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头、地板
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// 改变方向
				m_dir = Common::LEFT;
				if (!_isCrazy)
				{
					stopAllActions();
					this->runAction(Common::GetAnimateForeverActionByCacheName(IT_TORTOISE_MOVING_LEFT_ANIMATE_NAME));
				}
				return false;
			}
		}
	}
	return true;
}
bool ItemTortoise::canMoveDown(float dt)
{
	if (m_bIsDead)
		return false;
	return ItemMove::canMoveDown(dt);
}

bool ItemTortoise::canMove(float dt)
{
	if (m_bIsDead)
		return false;
	if (_isSleep)
		return false;
	if (!isLeftInWindow())
	{
		return false;
	}

	if (m_dir == Common::LEFT)
		return canMoveLeft(dt);
	return canMoveRight(dt);
}

void ItemTortoise::moveDown(float dt)
{
	ItemMove::moveDown(dt);
}
void ItemTortoise::move(float dt)
{
	if (canMove(dt))
	{
		if (m_dir == Common::LEFT)
		{
			ItemMove::moveLeft(dt);
		}
		else
		{
			ItemMove::moveRight(dt);
		}
	}
	CCRect rcItem = boundingBox();
	CCTMXTiledMap * map = getMap();
	// 碰到障碍物
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMidX(), rcItem.getMinY() - dt*m_speedDown);
	pt[1] = ccp(rcItem.getMinX(), rcItem.getMinY() - dt*m_speedDown);
	pt[2] = ccp(rcItem.getMaxX(), rcItem.getMinY() - dt*m_speedDown);
	moveDown(dt);
	if (isFarAwayFromMario())
	{
		removeFromParent();
	}
}

void ItemTortoise::unsetGodMode(float dt)
{
	_isGod = false;
}
void ItemTortoise::revival(float dt)
{
	_isSleep = false;
	m_speed= 50;
	stopAllActions();
	if (m_dir == Common::LEFT)
	{
		runAction(Common::GetAnimateForeverActionByCacheName(IT_TORTOISE_MOVING_LEFT_ANIMATE_NAME));
	}
	else
	{
		runAction(Common::GetAnimateForeverActionByCacheName(IT_TORTOISE_MOVING_RIGHT_ANIMATE_NAME));
	}
}

void ItemTortoise::collision()
{
	// 防止持续碰撞检测
	if (m_bIsDead) return;
	if (_isGod) return;
	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = this->boundingBox();
	// 判断碰撞检测
	if (this->boundingBox().intersectsRect(_mario->boundingBox()))
	{
		if (!_isSleep)
		{
			if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
			{
				stopAllActions();
				runAction(Common::GetAnimateForeverActionByCacheName("TortoiseDead"));
				// 无敌一段时间
				_isGod = true;
				scheduleOnce(schedule_selector(ItemTortoise::unsetGodMode), 0.2f);
				// 过一段时间要复活
				scheduleOnce(schedule_selector(ItemTortoise::revival), 10.0f);
				_isSleep = true;
				m_speed= 0;
				_mario->bounce();
			}
			else
			{
				_mario->Die(false);
			}
			return;
		}
		// 在乌龟处于_isCrazy ，乌龟应该快速移动
		else
		{
			m_speed= 200;
			_isCrazy = true;
			// 取消复活
			unschedule(schedule_selector(ItemTortoise::revival));
			// 无敌一段时间
			_isGod = true;
			scheduleOnce(schedule_selector(ItemTortoise::unsetGodMode), 0.2f);
			_isSleep = false;
			if (_mario->getPositionX() < getPositionX())
			{
				m_dir = Common::RIGHT;
			}
			else
			{
				m_dir = Common::LEFT;
			}
		}

	}
}
