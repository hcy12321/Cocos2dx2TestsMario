#ifndef __LAYERSTART_H__
#define __LAYERSTART_H__

#include "Common.h"
// ≥ı º≥°æ∞
class LayerStart : public CCLayer
{
public:
	CREATE_FUNC(LayerStart);
	bool init();

	void Start(CCObject *);
	void Setup(CCObject *);
	void Quit(CCObject *);
	void About(CCObject *);
};
#endif // !__LAYERSTART_H__

