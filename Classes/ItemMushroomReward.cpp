#include "ItemMushroomReward.h"
#include "Mario.h"


ItemMushroomReward * ItemMushroomReward::create(CCDictionary * dict)
{
	ItemMushroomReward * ret = new ItemMushroomReward;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemMushroomReward::init(CCDictionary * dict)
{
	ItemMove::init();
	_type = Item::IT_MUSHROOMREWARD;
	m_status = SLEEP;
	setPositionByProperty(dict);

	// ��������
	m_arrItemReward->addObject(this);

	m_dir = Common::LEFT;
	m_speed = 50;
	m_speedDown = m_speedAcc = 10;

	//setDisplayFrameWithAnimationName(IT_MUSHROOM_REWARD, 0);
	setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(IT_MUSHROOM_REWARD));
	setZOrder(0);
	setVisible(false);
	return true;
}

void ItemMushroomReward::wakeup()
{
	m_status = GROW;
	updateStatus();
	setVisible(true);
}
void ItemMushroomReward::updateStatus()
{
	if (m_status == GROW)
	{
		CCMoveBy * moveBy = CCMoveBy::create(1.0f, ccp(0, 16));
		CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(ItemMushroomReward::afterGrow));
		runAction(CCSequence::createWithTwoActions(moveBy, callFunc));
	}
}
void ItemMushroomReward::afterGrow()
{
	m_status = MOVE;
	updateStatus();
	setZOrder(100);
}

void ItemMushroomReward::move(float dt)
{
	if (m_status != MOVE) return;
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

	moveDown(dt);
	// ����
	if (isFarAwayFromMario())
	{
		removeFromParent();
	}
}

bool ItemMushroomReward::canMoveLeft(float dt)
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

bool ItemMushroomReward::canMoveRight(float dt)
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
bool ItemMushroomReward::canMoveDown(float dt)
{
	if (m_status != MOVE) return false;

	CCRect rcItem = boundingBox();
	CCTMXTiledMap * map = getMap();
	if (map == NULL)
	{
		return false;
	}
	// �����ϰ���
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMidX(), rcItem.getMinY() - dt*m_speedDown);
	pt[1] = ccp(rcItem.getMinX(), rcItem.getMinY() - dt*m_speedDown);
	pt[2] = ccp(rcItem.getMaxX(), rcItem.getMinY() - dt*m_speedDown);
	if (pt[0].y >= map->getContentSize().height || pt[0].y <= 0)
		return true;
	if (pt[0].y <= -rcItem.size.height)
		return false;

	// ����ת������ptת��Ϊ��ͼ�������꣬Ȼ���ȡgid���ж�gid�ǲ��Ǳ��赲
	for (int i = 0; i < 3; ++i)
	{

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
				// ΢��
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile + ccp(0, -1));
				this->setPositionY(ptLB.y);
				return false;
			}
		}
	}
	return true;
}

bool ItemMushroomReward::canMove(float dt)
{

	if (m_dir == Common::LEFT)
		return canMoveLeft(dt);
	return canMoveRight(dt);
}

void ItemMushroomReward::moveDown(float dt)
{
	if (canMoveDown(dt))
	{
		Common::moveNode(this, ccp(0, -dt * m_speedDown));
		m_speedDown += m_speedAcc;
	}
	else
	{
		m_speedDown = m_speedAcc;
	}
}

void ItemMushroomReward::collision()
{
	if (m_status != MOVE)
		return;
	if (_mario->boundingBox().intersectsRect(boundingBox()))
	{
		_mario->eatMushroom(this->_type);
		removeFromParent();
	}
}