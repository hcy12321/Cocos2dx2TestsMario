#ifndef __LAYERMENU_H__
#define __LAYERMENU_H__

#include "Common.h"
// ักนุ
class LayerMenu : public CCLayer
{
public:
	CREATE_FUNC(LayerMenu);
	bool init();

	void Back(CCObject *);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	bool isClick(CCTouch * pTouch);
	

	CCScrollView * _view;
};
#endif // !__LAYERMENU_H__

