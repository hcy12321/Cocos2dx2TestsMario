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
	// 创建背景精灵
	_bg = CCSprite::create(bgFile);
	addChild(_bg);
	// 创建前景精灵
	CCSprite * fore = CCSprite::create(foreFile);
	_bar = CCProgressTimer::create(fore);
	// 设置条形的，从左到右运动的进度条
	_bar->setType(kCCProgressTimerTypeBar);
	_bar->setMidpoint(ccp(0, 0)); // 中心点移到起点
	_bar->setBarChangeRate(ccp(1, 0));// x增长，y不增长

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