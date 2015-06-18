#include "ItemFireString.h"
#include "Mario.h"

ItemFireString * ItemFireString::create(CCDictionary* dict)
{
	ItemFireString * ret = new ItemFireString;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemFireString::init(CCDictionary * dict)
{
	Item::init();
	_type = IT_FIRESTRING;
	setPositionByProperty(dict);

	CCTexture2D * bossBullet = CCTextureCache::sharedTextureCache()->addImage("bossBullet.png");
	setTexture(bossBullet);
	setTextureRect(CCRectMake(0, 0, bossBullet->getContentSize().width, bossBullet->getContentSize().height));
	setScale(.6f);

	setAnchorPoint(ccp(0, 0.5f));

	int begAngle  = dict->valueForKey("begAngle")->intValue();
	setRotation(begAngle);
	int time = dict->valueForKey("time")->intValue();
	runAction(CCRepeatForever::create(CCRotateBy::create(time, 360)));

	return true;
}

void ItemFireString::collision()
{
	if (_mario->_dead) return;
	// 获取fireString线段
	struct Line
	{
		CCPoint pt1;
		CCPoint pt2;
	} lineFireString;

	CCRect rcItem = boundingBox();
	int angle = getRotation();
	angle %= 360;
	if (angle > 270)
	{
		lineFireString.pt1 = ccp(rcItem.getMinX(), rcItem.getMinY());
		lineFireString.pt2 = ccp(rcItem.getMaxX(), rcItem.getMaxY());
	}
	else if (angle > 180)
	{
		lineFireString.pt1 = ccp(rcItem.getMinX(), rcItem.getMaxY());
		lineFireString.pt2 = ccp(rcItem.getMaxX(), rcItem.getMinY());
	}
	else if (angle > 90)
	{
		lineFireString.pt1 = ccp(rcItem.getMinX(), rcItem.getMinY());
		lineFireString.pt2 = ccp(rcItem.getMaxX(), rcItem.getMaxY());
	}
	else
	{
		lineFireString.pt1 = ccp(rcItem.getMinX(), rcItem.getMaxY());
		lineFireString.pt2 = ccp(rcItem.getMaxX(), rcItem.getMinY());
	}


	// Mario线段
	Line lineMario[2];
	CCRect rcMario = _mario->boundingBox();
	lineMario[0].pt1 = ccp(rcMario.getMinX(), rcMario.getMinY());
	lineMario[0].pt2 = ccp(rcMario.getMaxX(), rcMario.getMaxY());
	lineMario[1].pt1 = ccp(rcMario.getMaxX(), rcMario.getMinY());
	lineMario[1].pt2 = ccp(rcMario.getMinX(), rcMario.getMaxY());

	for (int i = 0; i < 2; ++i)
	{
		if (ccpSegmentIntersect(lineMario[i].pt1, lineMario[i].pt2, lineFireString.pt1, lineFireString.pt2))
			_mario->Die(false);
	}

}