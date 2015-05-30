#ifndef __COMMON_H__
#define __COMMON_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

#define winSize CCDirector::sharedDirector()->getWinSize()
#define POINTET_HALFWINDOW ccp(winSize.width / 2, winSize.height / 2)
#define MARIOSPEED 2


#define IT_MUSHROOM_MOVING_ANIMATE_NAME "MushroomMoving"
#define IT_MUSHROOM_DEAD1_NAME "MushroomDead1"
#define IT_MUSHROOM_DEAD2_NAME "MushroomDead2"
#define IT_TORTOISE_MOVING_LEFT_ANIMATE_NAME "TortoiseMovingLeft"
#define IT_TORTOISE_MOVING_RIGHT_ANIMATE_NAME "TortoiseMovingRight"
#define IT_TORTOISE_FLY_LEFT_ANIMATE_NAME "TortoiseFlyLeft"
#define IT_TORTOISE_FLY_RIGHT_ANIMATE_NAME "TortoiseFlyRight"
#define IT_TORTOISE_DEAD "TortoiseDead"
#define IT_FLOWER_SHOW "FlowerShow"
#define IT_MUSHROOM_REWARD "MushroomReward"
#define IT_MUSHROOM_ADD_LIFE "MushroomAddLife"
#define IT_FLY_FISH_LEFT "FlyFishLeft"
#define IT_FLY_FISH_RIGHT "FlyFishRight"

struct Common
{
public:
	enum DIRECTON
	{
		LEFT, RIGHT, UP, DOWN, NONE
	};
	static CCScene * scene(CCLayer* layer)
	{
		CCScene * s = CCScene::create();
		s->addChild(layer);
		return s;
	}
	static void moveNode(CCNode * node, CCPoint pt)
	{
		node->setPosition(node->getPosition() + pt);
	}

	static char * format(int v, const char * prefix = "", const char * suffix = "")
	{
		static char buf[2048];
		sprintf(buf, "%s%d%s", prefix, v, suffix);
		return buf;
	}

	static CCAnimation * CreateAnimation(const char * filename, int start, int end, int width, float delay)
	{
		CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		CCArray * arr = CCArray::create();
		for (int i = start; i <= end; ++i)
		{
			CCSpriteFrame * frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(i * width, 0, width, texture->getContentSize().height));
			arr->addObject(frame);
		}
		return CCAnimation::createWithSpriteFrames(arr, delay);
	}

	static CCSpriteFrame * getSpriteFrame(const char * filename, int pos, int width)
	{
		CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		CCSpriteFrame * frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(pos * width, 0, width, texture->getContentSize().height));
		return frame;
	}

	static CCPoint Point2Tile(CCTMXTiledMap * map, CCPoint ptMap)
	{
		int dx = map->getTileSize().width;
		int dy = map->getTileSize().height;

		int x = ptMap.x / dx;
		int y = ptMap.y / dy;
		y = map->getMapSize().height - 1 - y;
		return ccp(x, y);
	}
	static CCPoint Tile2PointLB(CCTMXTiledMap * map, CCPoint ptTile)
	{
		ptTile.y = map->getMapSize().height - 1 - ptTile.y;
		return ccp(ptTile.x * map->getTileSize().width,
			ptTile.y * map->getTileSize().height);
	}

	static CCAction * GetAnimateForeverActionByCacheName(const char * name)
	{
		return CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(name)));
	}

};


#endif // !__COMMON_H__
