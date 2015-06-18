#ifndef __ITEM_H__
#define __ITEM_H__

#include "Common.h"
class Mario;
class Item : public CCSprite
{
public:
	enum ItemType{
		IT_MUSHROOM, IT_TORTOISE, IT_FLOWER, IT_MUSHROOMREWARD, IT_MUSHROOMADDLIFE, IT_FLAGPOINT, IT_FINALPOINT, IT_LADDERLR, IT_LADDERUD,
		IT_FLYFISH, IT_ITEMTORTOISEROUND, IT_TORTOISEFLY, IT_FIRESTRING, IT_BOSS, IT_BULLET, IT_BRIDGE_POS
	};
	virtual ~Item();
	bool init();
	static Item * create(CCDictionary* dict);
	void update(float delta);
	virtual void runAnimation(const char * name);

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
	CCAction * m_actionForStop;
	static Item * _Flag;
	static CCArray * m_arrItemReward;
	static Item * m_boss;
	static Item * m_bridge;
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




