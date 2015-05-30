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

	// ����
	m_nLorR = dict->valueForKey("LorR")->intValue(); // һ��ʼ����������
	m_nladderDis = dict->valueForKey("ladderDis")->intValue(); // �ڶ�����
	m_speed = 20;
	m_ndis = 0;
	m_bMarioOnThisLadder = false;
	return true;
}

void ItemLadderLR::move(float dt)
{
	// �ƶ�
	if (m_nLorR > 0) // ����
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
	// �ۼ��ƶ��ľ��룬�ж�ת��
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
	// ��������ײ
	if (rcItem.intersectsRect(rcMario))
	{
		// �Դ�ײ����
		if (_mario->_speedUp > 0)
		{
			_mario->_speedDown = _mario->_speedUp;
			_mario->_speedUp = 0;
		}
		else
		{
			// ����_mario->_onLadder 
			if (_mario->_bFly)
			{
				// �����
				_mario->_onLadder = true;
				// ΢��
				//_mario->setPositionY(rcItem.getMaxY());
				// mario�����������
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