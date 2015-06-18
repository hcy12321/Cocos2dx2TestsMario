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

	// ����
	m_nUorD = dict->valueForKey("UorD")->intValue(); // һ��ʼ����������
	m_nladderDis = dict->valueForKey("ladderDis")->intValue(); // �ڶ�����
	m_speed = 20;
	m_fdis = 0;
	m_bmarioOnThisLadder = false;
	return true;
}

void ItemLadderUD::move(float dt)
{
	// �ƶ�
	if (m_nUorD > 0) // ����
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
	// �ۼ��ƶ��ľ��룬�ж�ת��
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