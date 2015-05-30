#ifndef __ITEM_H__
#define __ITEM_H__

#include "Common.h"
class Mario;
class Item : public CCSprite
{
public:
	enum ItemType{ IT_MUSHROOM, IT_TORTOISE, IT_FLOWER, IT_MUSHROOMREWARD, IT_MUSHROOMADDLIFE, IT_FLAGPOINT, IT_FINALPOINT, IT_LADDERLR,
		IT_FLYFISH, IT_ITEMTORTOISEROUND,IT_TORTOISEFLY
	};
	virtual ~Item();
	bool init();
	static Item * create(CCDictionary* dict);
	void update(float delta);

	// 对象虚接口
	virtual void move(float dt);
	virtual void collision();
	virtual void wakeup();
	
	//////////////////////////////////////////////////////////////////////////公共辅助函数
	void setPositionByProperty(CCDictionary *dict);
	CCTMXTiledMap * getMap();
	bool isLeftInWindow();
	bool isFarAwayFromMario();

	ItemType _type;
	Mario * _mario;
	static Item * _Flag;
	static CCArray * m_arrItemReward;
};

/*
class ItemFactory
{
public:
	Item * createItem(Item::ItemType it)
	{
		return Item::create(it);
	}
};
*/
#endif // !__ITEM_H__




