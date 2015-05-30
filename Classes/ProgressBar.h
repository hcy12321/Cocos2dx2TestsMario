#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

#include "Common.h"

class ProgressBar:public CCLayer
{
public:
	static ProgressBar * create(const char * bgFile, const char * foreFile);
	bool init(const char * bgFile, const char * foreFile);

	void setPercentage(float per);
	float getPercentage();
	void setPosition(CCPoint position);

private:
	CCProgressTimer * _bar;
	CCSprite * _bg;

};


#endif // !__PROGRESSBAR_H__


