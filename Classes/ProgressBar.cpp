#include "ProgressBar.h"

ProgressBar * ProgressBar::create(const char * bgFile, const char * foreFile)
{
	ProgressBar * ret = new ProgressBar;
	ret->init(bgFile, foreFile);
	ret->autorelease();
	return ret;
}


bool ProgressBar::init(const char * bgFile, const char * foreFile)
{
	CCLayer::init();
	// ������������
	_bg = CCSprite::create(bgFile);
	addChild(_bg);
	// ����ǰ������
	CCSprite * fore = CCSprite::create(foreFile);
	_bar = CCProgressTimer::create(fore);
	// �������εģ��������˶��Ľ�����
	_bar->setType(kCCProgressTimerTypeBar);
	_bar->setMidpoint(ccp(0, 0)); // ���ĵ��Ƶ����
	_bar->setBarChangeRate(ccp(1, 0));// x������y������

	_bar->setPercentage(0);
	addChild(_bar);
	return true;
}
void ProgressBar::setPercentage(float per)
{
	_bar->setPercentage(per);
}
float ProgressBar::getPercentage()
{
	return _bar->getPercentage();
}

void ProgressBar::setPosition(CCPoint position)
{
	_bar->setPosition(position);
	_bg->setPosition(position);
}