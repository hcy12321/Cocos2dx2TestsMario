#include "ItemFlyFish.h"
#include "Mario.h"

ItemFlyFish * ItemFlyFish::create(CCDictionary* dict)
{
	ItemFlyFish * ret = new ItemFlyFish;
	ret->init(dict);
	ret->autorelease();
	return ret;
}

bool ItemFlyFish::init(CCDictionary * dict)
{
	Item::init();
	_type = Item::IT_FLYFISH;
	setPositionByProperty(dict);

	m_nduration = dict->valueForKey("duration")->intValue();
	m_noffsetH = dict->valueForKey("offsetH")->intValue();
	m_noffsetV = dict->valueForKey("offsetV")->intValue();
	m_balreadyFly = false;

	m_dir = m_noffsetH > 0 ? Common::RIGHT : Common::LEFT;
	return true;
}

void ItemFlyFish::updateStatus()
{
	stopAllActions();
	CCAnimation * animation;
	if (m_dir == Common::LEFT)
	{
		animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_FLY_FISH_LEFT);
	}
	else
	{
		animation = CCAnimationCache::sharedAnimationCache()->animationByName(IT_FLY_FISH_RIGHT);
	}

	if (animation == NULL)
		return;
	
	CCAnimate * animate = CCAnimate::create(animation);
	CCRepeatForever * rep = CCRepeatForever::create(animate);
	runAction(rep);
}

void ItemFlyFish::move(float dt)
{
	//if (!this->isLeftInWindow())
	//	return;
	if (getPositionX() > _mario->getPositionX()) 
		return;
	if (m_balreadyFly)
		return;
	m_balreadyFly = true;

	updateStatus();
	// ÈÃ·ÉÓã×ö±´Èû¶ûÇúÏßÔË¶¯
	ccBezierConfig c;
	c.controlPoint_1.x = CCRANDOM_0_1() * m_noffsetH;
	c.controlPoint_1.y = CCRANDOM_0_1() * m_noffsetV;
	c.controlPoint_2.x = CCRANDOM_0_1() * m_noffsetH;
	c.controlPoint_2.y = CCRANDOM_0_1() * m_noffsetV;
	c.endPosition = ccp(m_noffsetH, m_noffsetV);
	CCBezierBy * bezier = CCBezierBy::create(m_nduration, c);

	ccBezierConfig c1;
	c1.controlPoint_1.x = CCRANDOM_0_1() * m_noffsetH;
	c1.controlPoint_1.y = CCRANDOM_0_1() * m_noffsetV;
	c1.controlPoint_2.x = CCRANDOM_0_1() * m_noffsetH;
	c1.controlPoint_2.y = CCRANDOM_0_1() * m_noffsetV;
	c1.endPosition = ccp(m_noffsetH, -m_noffsetV);
	CCBezierBy * bezier1 = CCBezierBy::create(m_nduration, c1);

	CCCallFunc * callfunc = CCCallFunc::create(this, callfunc_selector(ItemFlyFish::removeFromParent));


	runAction(CCSequence::create(bezier, bezier1, callfunc, NULL));


}

void ItemFlyFish::collision()
{
	if (_mario->boundingBox().intersectsRect(this->boundingBox()))
	{
		_mario->Die(false);
	}
}