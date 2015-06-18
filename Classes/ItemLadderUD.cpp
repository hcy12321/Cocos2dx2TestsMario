#include "ItemLadderUD.h"
#include "Mario.h"

ItemLadderUD * ItemLadderUD::create(CCDictionary* dict)
{
	ItemLadderUD * ret = new ItemLadderUD;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemLadderUD::init(CCDictionary * dict)
{
	ItemMove::init();
	_type = Item::IT_LADDERUD;

	setPositionByProperty(dict);

	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("ladder.png");
	setTexture(texture);
	setTextureRect(CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height));

	Common::moveNode(this, ccp(-texture->getContentSize().width / 2, 0));

	// 属性
	m_nUorD = dict->valueForKey("UorD")->intValue(); // 一开始向左还是向右
	m_nladderDis = dict->valueForKey("ladderDis")->intValue(); // 摆动幅度
	m_speed = 20;
	m_fdis = 0;
	m_bmarioOnThisLadder = false;
	return true;
}

void ItemLadderUD::move(float dt)
{
	// 移动
	if (m_nUorD > 0) // 向下
	{
		Common::moveNode(this, ccp(0, -dt * m_speed));
		if (m_bmarioOnThisLadder)
		{
			Common::moveNode(_mario, ccp(0, -dt * m_speed));
		}
	}
	else
	{
		Common::moveNode(this, ccp(0, dt * m_speed));
		if (m_bmarioOnThisLadder)
		{
			Common::moveNode(_mario, ccp(0, dt * m_speed));
		}
	}
	// 累加移动的距离，判断转向
	m_fdis += dt * m_speed;
	if (m_fdis >= m_nladderDis)
	{
		m_nUorD = 1 - m_nUorD;
		m_fdis = 0;
	}
}

void ItemLadderUD::collision()
{
	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = boundingBox();
	// 和梯子碰撞
	if (rcItem.intersectsRect(rcMario))
	{
		// 脑袋撞上了
		if (_mario->_speedUp > 0)
		{
			_mario->_speedDown = _mario->_speedUp;
			_mario->_speedUp = 0;
		}
		else
		{
			// 设置_mario->_onLadder 
			if (_mario->_bFly)
			{
				// 刚落地
				_mario->_onLadder = true;
				// 微调
				//_mario->setPositionY(rcItem.getMaxY());
				// mario在我这个梯子
				m_bmarioOnThisLadder = true;
			}
		}
	}
	else
	{
		if (m_bmarioOnThisLadder)
		{
			_mario->_onLadder = false;
			m_bmarioOnThisLadder = false;
		}
	}

}