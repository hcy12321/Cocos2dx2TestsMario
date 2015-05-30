#include "ItemLadderLR.h"
#include "Mario.h"


ItemLadderLR * ItemLadderLR::create(CCDictionary * dict)
{
	ItemLadderLR * ret = new ItemLadderLR;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemLadderLR::init(CCDictionary * dict)
{
	ItemMove::init();
	_type = Item::IT_LADDERLR;

	setPositionByProperty(dict);

	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("ladder.png");
	setTexture(texture);
	setTextureRect(CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height));

	// 属性
	m_nLorR = dict->valueForKey("LorR")->intValue(); // 一开始向左还是向右
	m_nladderDis = dict->valueForKey("ladderDis")->intValue(); // 摆动幅度
	m_speed = 20;
	m_ndis = 0;
	m_bMarioOnThisLadder = false;
	return true;
}

void ItemLadderLR::move(float dt)
{
	// 移动
	if (m_nLorR > 0) // 向左
	{
		Common::moveNode(this, ccp(-dt * m_speed, 0));
		if (m_bMarioOnThisLadder)
		{
			Common::moveNode(_mario, ccp(-dt * m_speed, 0));
		}
	}
	else
	{
		Common::moveNode(this, ccp(dt * m_speed, 0));
		if (m_bMarioOnThisLadder)
		{
			Common::moveNode(_mario, ccp(dt * m_speed, 0));
		}
	}
	// 累加移动的距离，判断转向
	m_ndis += dt * m_speed;
	if (m_ndis >= m_nladderDis)
	{
		m_nLorR = 1 - m_nLorR;
		m_ndis = 0;
	}
}
void ItemLadderLR::collision()
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
				m_bMarioOnThisLadder = true;
			}
		}
	}
	else
	{
		if (m_bMarioOnThisLadder)
		{
			_mario->_onLadder = false;
			m_bMarioOnThisLadder = false;
		}
	}

}