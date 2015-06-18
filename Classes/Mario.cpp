#include "Mario.h"
#include "Item.h"
#include "LayerGame.h"

int Mario::_life = 0;

bool Mario::init()
{
	// 设置初始化图片
	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("smallWalkRight.png");
	CCSpriteFrame * frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, texture->getContentSize().width / 11, texture->getContentSize().height));
	CCSprite::initWithSpriteFrame(frame);
	// 设置最前
	setZOrder(100);
	// 自定义属性初始化
	_speed = 100;

	_speedUp = 0;
	_speedAcc = 10;
	_speedDown = _speedAcc;
	_dirRun = Common::NONE;
	_dirFace = Common::RIGHT;
	_isBig = false;
	_canFire = false;
	_bFly = false;
	_bGodMode = true;
	_dead = false;
	_autoRun = false;
	_flagRunAction = false;
	_onLadder = false;
	// mario用到的动画

	CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("smallWalkLeft.png", 0, 9, 14, 0.05f), "SmallWalkLeft");
	CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("smallWalkRight.png", 0, 9, 14, 0.05f), "SmallWalkRight");
	CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("walkLeft.png", 0, 9, 18, 0.05f), "BigWalkLeft");
	CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("walkRight.png", 0, 9, 18, 0.05f), "BigWalkRight");
	CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("small_die.png", 0, 6, 16, 0.05f), "smalldie");

	// mario用到的帧
	frame = Common::getSpriteFrame("smallWalkLeft.png", 10, 14);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "SmallJumpLeft");

	frame = Common::getSpriteFrame("smallWalkRight.png", 10, 14);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "SmallJumpRight");
	
	frame = Common::getSpriteFrame("walkRight.png", 10, 18);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "BigJumpLeft");

	frame = Common::getSpriteFrame("walkRight.png", 10, 18);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "BigJumpRight");

	return true;
}

void Mario::onExit()
{
	CCSprite::onExit();
}

CCTMXTiledMap * Mario::getMap()
{
	return (CCTMXTiledMap *)getParent();
}

void Mario::moveDir(float dt, Common::DIRECTON dir)
{
	if (_dirRun != dir)
	{
		_dirRun = dir;
		_dirFace = dir;
		updateStatus();
	}
}

void Mario::moveLeft(float dt)
{
	moveDir(dt, Common::LEFT);

	CCNode * map = getParent();
	CCPoint ptWorld = map->convertToWorldSpace(this->getPosition());
	if (!canMoveLeft(dt))
		return;
	Common::moveNode(this, ccp(-dt * _speed, 0));
}
void Mario::moveRight(float dt)
{
	moveDir(dt, Common::RIGHT);

	if (!canMoveRight(dt))
		return;

	Common::moveNode(this, ccp(dt * _speed, 0));
	// 获取地图最右点，判断是否需要卷动地图
	CCPoint ptLastInMap = ccp(getMap()->getContentSize().width, 5);
	CCPoint ptLastInWorld = getMap()->convertToWorldSpace(ptLastInMap);
	if (ptLastInWorld.x <= winSize.width) // 地图最后一个点在窗口内
		return;
	// 卷动地图
	// 如果mario位置超过了地图的一半，就该卷动地图
	// mario在世界坐标中的x坐标，超过了窗口的一半
	CCNode * map = getParent();
	CCPoint ptWorld = map->convertToWorldSpace(this->getPosition());
	if (ptWorld.x > winSize.width / 2)
	{
		Common::moveNode(map, ccp(-dt * _speed, 0));
	}
}

bool Mario::canMoveLeft(float dt)
{
	if (_dead) return false;
	// 跑到地图外
	CCRect rcMario = boundingBox();
	CCPoint ptMario = ccp(rcMario.getMinX(), rcMario.getMinY());
	CCTMXTiledMap * map = getMap();
	CCPoint ptMarioInWorld = map->convertToWorldSpace(ptMario);
	if (ptMarioInWorld.x - dt* _speed < 0)
		return false;
	// 碰到障碍物
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMinX() - dt*_speed, rcMario.getMidY());
	pt[1] = ccp(rcMario.getMinX() - dt*_speed, rcMario.getMinY());
	pt[2] = ccp(rcMario.getMinX() - dt*_speed, rcMario.getMaxY());
	// 坐标转换，讲pt转化为地图格子坐标，然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height || pt[i].y <= 0)
			continue;
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头、地板
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3;++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				return false;
			}
		}
	}
	return true;
}
bool Mario::canMoveRight(float dt)
{
	if (_dead) return false;
	CCRect rcMario = boundingBox();
	CCTMXTiledMap * map = getMap();
	// 碰到障碍物
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMaxX() + dt*_speed, rcMario.getMidY());
	pt[1] = ccp(rcMario.getMaxX() + dt*_speed, rcMario.getMinY());
	pt[2] = ccp(rcMario.getMaxX() + dt*_speed, rcMario.getMaxY());
	// 坐标转换，讲pt转化为地图格子坐标，然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height || pt[i].y <= 0)
			continue;
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头、地板
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				return false;
			}
		}
	}
	return true;
}

bool Mario::canMoveDown(float dt)
{
	//if (_autoRun) return false;
	if (_dead) return false;
	if (_onLadder) return false;
	CCRect rcMario = boundingBox();
	CCTMXTiledMap * map = getMap();
	// 碰到障碍物
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMidX(), rcMario.getMinY() - dt*_speedDown);
	pt[1] = ccp(rcMario.getMinX(), rcMario.getMinY() - dt*_speedDown);
	pt[2] = ccp(rcMario.getMaxX(), rcMario.getMinY() - dt*_speedDown);
	if (pt[0].y >= map->getContentSize().height || pt[0].y <= 0)
		return true;
	if (pt[0].y <= -rcMario.size.height)
		return false;
	// 坐标转换，讲pt转化为地图格子坐标，然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头、地板
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// 微调
				CCPoint ptLB =	Common::Tile2PointLB(map, ptTile + ccp(0, -1));
				this->setPositionY(ptLB.y);

				// 在自动运行情况下
				if (_autoRun && !_flagRunAction)
				{
					_flagRunAction = true;
					Item::_Flag->runAction(CCMoveTo::create(1, ccp(Item::_Flag->getPositionX(), getPositionY())));
				}
				return false;
			}
		}
	}
	return true;
}

bool Mario::canMoveUp(float dt)
{
	if (_dead) return false;
	CCRect rcMario = boundingBox();
	CCTMXTiledMap * map = getMap();
	// 碰到障碍物
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMidX(), rcMario.getMaxY() + dt*_speedUp);
	pt[1] = ccp(rcMario.getMinX(), rcMario.getMaxY() + dt*_speedUp);
	pt[2] = ccp(rcMario.getMaxX(), rcMario.getMaxY() + dt*_speedUp);

	if (pt[0].y >= map->getContentSize().height || pt[0].y <= 0)
		return true;

	// 坐标转换，讲pt转化为地图格子坐标，然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头、地板
		static const char * layerName[3] = {
			"block", "pipe", "land"
		};
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer * layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// 微调
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile + ccp(0, 1));
				this->setPositionY(ptLB.y);
				// 顶到东西了
				Hit(layerName[j], gid, ptTile);
				return false;
			}
		}
	}
	return true;
}

void Mario::Hit(const std::string& layername, int gid, CCPoint ptTile)
{
	if (layername != "block") return;

	CCTMXLayer * layer = getMap()->layerNamed(layername.c_str());
	if (gid == 1) // 普通砖头
	{

	}
	else if (gid == 601) // 问号
	{
		layer->setTileGID(31, ptTile);
	}
	else if (gid == 846) //
	{
		layer->setTileGID(31, ptTile);
	}

	if (gid == 31) return;
	CCSprite * sprite = layer->tileAt(ptTile);
	sprite->runAction(CCJumpBy::create(0.1f, ccp(0, 0), 8, 1));

	CCJumpBy * jump = CCJumpBy::create(0.1f, ccp(0, 0), 20, 1);
	CCCallFuncN * callfunc = CCCallFuncN::create(this, callfuncN_selector(Mario::wakeupMushroomReward));
	sprite->runAction(CCSequence::createWithTwoActions(jump, callfunc));	
}
// 检查砖头中是否有蘑菇
void Mario::wakeupMushroomReward(CCNode * node)
{
	CCSprite * sprite = (CCSprite *)node;
	// 唤醒隐藏的蘑菇奖赏
	CCObject * obj;
	CCARRAY_FOREACH(Item::m_arrItemReward, obj)
	{
		Item * item = (Item *)obj;
		CCRect rcBlock = sprite->boundingBox();
		rcBlock.origin = rcBlock.origin + ccp(4, 4);
		rcBlock.size.width /= 2;
		rcBlock.size.height /= 2;
		if (item->boundingBox().intersectsRect(rcBlock))
		{
			item->wakeup();
			break;
		}
	}
}
void Mario::stop()
{
	if (_dirRun != Common::NONE)
	{
		_dirRun = Common::NONE;
		updateStatus();
	}
}

void Mario::jump()
{
	if (_bFly || _autoRun || _dead)
		return;
	_speedUp = 280;
	_bFly = true;
	updateStatus();
}

void Mario::bounce()
{
	_speedUp = 80;
	_speedDown = _speedAcc;
}

void Mario::moveUp(float dt)
{
	if (_speedUp <= 0)
	{
		return;
	}
	if (!canMoveUp(dt))
	{
		_speedDown = _speedUp;
		_speedUp = 0;
		return;
	}
	Common::moveNode(this, ccp(0, dt * _speedUp));
	_speedUp -= _speedAcc;
	//_speedDown = _speedUp;
}

void Mario::moveDown(float dt)
{
	if (_speedUp <= 0)
	{
		if (canMoveDown(dt))
		{
			if (!_bFly)
			{
				_bFly = true;
				updateStatus();
			}
			Common::moveNode(this, ccp(0, -dt*_speedDown));
			_speedDown += _speedAcc;
		}
		else
		{
			if (_bFly)
			{
				_bFly = false;
				_speedDown = _speedAcc;
				updateStatus();
			}
		}
	}
}

void Mario::Dead()
{
	//LayerGame::GameOver();
}

void Mario::updateStatus()
{
	stopAllActions();
	if (_autoRun)
	{
		if (_isBig)
			setDisplayFrameWithAnimationName("BigWalkRight", 0);
		else
			setDisplayFrameWithAnimationName("SmallWalkRight", 0);
		return;
	}
	if (_dead)
	{
		CCAnimation * animation = CCAnimationCache::sharedAnimationCache()->animationByName("smalldie");
		CCAnimate * animate = CCAnimate::create(animation);
		CCMoveBy * moveBy = CCMoveBy::create(winSize.height/ _speed, ccp(0, -winSize.height));
		//CCCallFunc * callfunc = CCCallFunc::create(this, callfunc_selector(Mario::Dead));

		CCSequence  * seq = CCSequence::create(animate, moveBy, NULL);
		runAction(seq);
		return;
	}
	if (_bFly)
	{
		if (_isBig)
		{
			if (_dirFace == Common::LEFT)
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BigJumpLeft"));
			}
			else
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BigJumpRight"));
			}
		}
		else
		{
			if (_dirFace == Common::LEFT)
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SmallJumpLeft"));
			}
			else
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SmallJumpRight"));
			}
		}
		return;
	}
	if (_isBig)
	{
		if (_dirRun == Common::LEFT)
		{
			//runAction
			runAction(Common::GetAnimateForeverActionByCacheName("BigWalkLeft"));
		}
		else if (_dirRun == Common::RIGHT)
		{
			runAction(Common::GetAnimateForeverActionByCacheName("BigWalkRight"));
		}
		else // 静止
		{
			if (_dirFace == Common::LEFT)
			{
				this->setDisplayFrameWithAnimationName("BigWalkLeft", 0);
			}
			else
			{
				this->setDisplayFrameWithAnimationName("BigWalkRight", 0);
			}
		}
	}
	else
	{
		if (_dirRun == Common::LEFT)
		{
			//runAction
			runAction(Common::GetAnimateForeverActionByCacheName("SmallWalkLeft"));
		}
		else if (_dirRun == Common::RIGHT)
		{
			runAction(Common::GetAnimateForeverActionByCacheName("SmallWalkRight"));
		}
		else // 静止
		{
			if (_dirFace == Common::LEFT)
			{
				this->setDisplayFrameWithAnimationName("SmallWalkLeft", 0);
			}
			else
			{
				this->setDisplayFrameWithAnimationName("SmallWalkRight", 0);
			}
		}
	}
	
}

void Mario::Die(bool dead)
{
	if (_dead) return;
	// 掉沟里
	if (dead)
	{
		_dead = true;
	}

	// 无敌模式
	if (!dead && this->_bGodMode)return;
	if (!dead && _isBig )
	{
		_isBig = false;
		updateStatus();
		// 无敌一段时间
		setGodMode(5);
		return;
	}
	_dead = true;
	updateStatus();
}
void Mario::eatMushroom(Item::ItemType type)
{
	if (type == Item::IT_MUSHROOMREWARD)
	{
		if (!_isBig)
		{
			_isBig = true;
			updateStatus();
		}
	}
	else if (type == Item::IT_MUSHROOMADDLIFE)
	{
		_life++;
	}
}
void Mario::unsetGodMode(float)
{
	this->_bGodMode = false;
}
void Mario::setGodMode(int time)
{
	this->_bGodMode = true;
	scheduleOnce(schedule_selector(Mario::unsetGodMode), time);
}

void Mario::autoRun()
{
	_autoRun = true;
	updateStatus();
	_speedUp = 0;
	_speedDown = 10;
	schedule(schedule_selector(Mario::moveDown));
}
void Mario::autoRun2()
{
	schedule(schedule_selector(Mario::walkForward));
}
void Mario::walkForward(float dt)
{
	moveRight(dt);
}