#include "ItemMushroom.h"
#include "Mario.h"

ItemMushroom * ItemMushroom::create(CCDictionary * dict)
{
	ItemMushroom * ret = new ItemMushroom;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemMushroom::init(CCDictionary * dict)
{
	ItemMove::init();
	_type = Item::IT_MUSHROOM;
	// ����λ��
	setPositionByProperty(dict);
	// ����ͼƬ(�������ö������Բ�������ͼƬ)
	//setDisplayFrameWithAnimationName(IT_MUSHROOM_MOVING_ANIMATE_NAME, 0);

	m_dir = Common::LEFT;
	m_speed = 50;
	m_speedDown = m_speedAcc = 10;
	m_bIsDead = false;
	// ���ض���
	this->runAction(Common::GetAnimateForeverActionByCacheName(IT_MUSHROOM_MOVING_ANIMATE_NAME));
	return true;
}

bool ItemMushroom::canMoveLeft(float dt)
{
	// �ܵ���ͼ��
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

	// �����ϰ���
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMinX() - dt*m_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMinX() - dt*m_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMinX() - dt*m_speed, rcItem.getMaxY());
	// ����ת������ptת��Ϊ��ͼ�������꣬Ȼ���ȡgid���ж�gid�ǲ��Ǳ��赲
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height || pt[i].y <= 0)
			continue;
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// ˮ�ܡ�שͷ���ذ�
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				//�仯����
				m_dir = Common::RIGHT;
				return false;
			}
		}
	}
	return true;
}
bool ItemMushroom::canMoveRight(float dt)
{
	CCRect rcItem = boundingBox();
	CCTMXTiledMap * map = getMap();
	if (map == NULL)
	{
		return false;
	}
	// �����ϰ���
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMaxX() + dt*m_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMaxX() + dt*m_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMaxX() + dt*m_speed, rcItem.getMaxY());
	// ����ת������ptת��Ϊ��ͼ�������꣬Ȼ���ȡgid���ж�gid�ǲ��Ǳ��赲
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height || pt[i].y <= 0)
			continue;
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// ˮ�ܡ�שͷ���ذ�
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// �ı䷽��
				m_dir = Common::LEFT;
				return false;
			}
		}
	}
	return true;
}
bool ItemMushroom::canMoveDown(float dt)
{
	if (m_bIsDead)
		return false;
	
	return ItemMove::canMoveDown(dt);
}

bool ItemMushroom::canMove(float dt)
{
	if (m_bIsDead)
		return false;
	if (!isLeftInWindow())
	{
		return false;
	}

	if (m_dir == Common::LEFT)
		return canMoveLeft(dt);
	return canMoveRight(dt);
}

void ItemMushroom::moveDown(float dt)
{
	ItemMove::moveDown(dt);
}
void ItemMushroom::move(float dt)
{
	if (canMove(dt))
	{
		if (m_dir == Common::LEFT)
		{
			Common::moveNode(this, ccp(-dt * m_speed, 0));
		}
		else
		{
			Common::moveNode(this, ccp(dt * m_speed, 0));
		}
	}
	CCRect rcItem = boundingBox();
	CCTMXTiledMap * map = getMap();
	// �����ϰ���
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

void ItemMushroom::collision()
{
	if (m_bIsDead) return;
	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = this->boundingBox();
	if (rcItem.intersectsRect(rcMario))
	{
		if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
		{
			this->stopAllActions();
			this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(IT_MUSHROOM_DEAD1_NAME));
			m_speed = 0;
			m_bIsDead = true;
			this->runAction(CCMoveBy::create(3.0f, ccp(0, -winSize.height)));
			_mario->bounce();
		}
		else
		{
			_mario->Die(false);
		}
	}
}
