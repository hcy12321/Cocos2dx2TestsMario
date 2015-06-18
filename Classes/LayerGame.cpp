#include "LayerGame.h"
#include "LayerMenu.h"
#include "LayerStart.h"
#include "MenuCtrl.h"
#include "Item.h"

int LayerGame::_idx = 0;

LayerGame * LayerGame::create(int idx)
{
	LayerGame * ret = new LayerGame;
	ret->init(idx);
	ret->autorelease();
	return ret;
}


bool LayerGame::init(int idx)
{
	CCLayer::init();
	// 地图编号
	_idx = idx;
	// 初始化怪物
	//_items = CCArray::create();
	//_items->retain();

	// 进度条
	_bar = ProgressBar::create("sliderTrack.png", "sliderProgress.png");
	addChild(_bar);
	_bar->setPosition(POINTET_HALFWINDOW);
	_bar->setPercentage(100);

	// 加载资源
	loadResource();
	// 开启默认定时
	scheduleUpdate();
	return true;
}

void LayerGame::update(float delta)
{

}

void LayerGame::onEnter()
{
	CCLayer::onEnter();
}
void LayerGame::onExit()
{
	CCLayer::onExit();
//	_items->release();
}

void LayerGame::loadResource()
{

	// picture, music
	static const char * picfiles[] = {
		"about_normal.png",
		"about_select.png",
		"AB_normal.png",
		"AB_select.png",
		"allow_walkLeft.png",
		"allow_walkRight.png",
		"arrow.png",
		"arrowActionL.png",
		"arrowActionR.png",
		"arrowBroken.png",
		"arrowBullet.png",
		"arrow_die.png",
		"axe.png",
		"backA.png",
		"backB.png",
		"background.png",
		"backKeyImage.png",
		"backKeyLeft.png",
		"backKeyRight.png",
		"backToMenu.png",
		"battery.png",
		"batteryBoom1.png",
		"batteryBoom2.png",
		"batteryBoom3.png",
		"batteryBullet.png",
		"bg.png",
		"blinkcoin.png",
		"boss.png",
		"bossBullet.png",
		"brokencoin.png",
		"bulletBorder.png",
		"CloseNormal.png",
		"CloseSelected.png",
		"cloud.png",
		"coinani.png",
		"controlUI.png",
		"darkCloud.png",
		"fireActionL.png",
		"fireActionR.png",
		"fireBall.png",
		"fireLeft.png",
		"fireRight.png",
		"fire_die.png",
		"flag.png",
		"flower0.png",
		"flyFishLeft.png",
		"flyFishRight.png",
		"fps_images-hd.png",
		"fps_images-ipadhd.png",
		"fps_images.png",
		"gameover.png",
		"ladder.png",
		"left.png",
		"leftright.png",
		"lighting.png",
		"Mushroom0.png",
		"music_off.png",
		"music_on.png",
		"M_n.png",
		"M_s.png",
		"newgameA.png",
		"newgameB.png",
		"nextlevel_normal.png",
		"nextlevel_select.png",
		"normal_die.png",
		"PassFailure.png",
		"PassSuccess.png",
		"princess.png",
		"quitgame_normal.png",
		"quitgame_select.png",
		"restart_n.png",
		"restart_s.png",
		"resume_n.png",
		"resume_s.png",
		"retry_normal.png",
		"retry_select.png",
		"rewardMushroomSet.png",
		"right.png",
		"select_n.png",
		"select_s.png",
		"Setting_n.png",
		"setting_s.png",
		"Set_Menu.png",
		"Set_Music.png",
		"set_n.png",
		"set_s.png",
		"shanshuodecoin.png",
		"singleblock.png",
		"sliderProgress.png",
		"sliderTrack.png",
		"smallWalkLeft.png",
		"smallWalkRight.png",
		"small_die.png",
		"sound_effect_off.png",
		"sound_effect_on.png",
		"startgame_normal.png",
		"startgame_select.png",
		"superMarioMap.png",
		"switchBg.png",
		"Tools.png",
		"tortoise0.png",
		"walkLeft.png",
		"WalkLeft_fire.png",
		"walkRight.png",
		"WalkRight_fire.png",
	};

	static const char * musicfile[] = {
		"EatCoin.wma",
	};
	_totalfile = sizeof(picfiles) / sizeof(*picfiles);
	int musicFileCount = sizeof(musicfile) / sizeof(*musicfile);

	for (int i = 0; i < musicFileCount; ++i)
	{
		SimpleAudioEngine::sharedEngine()->preloadEffect(musicfile[i]);
	}
	_loadFileCount = 0;
	for (int i = 0; i < _totalfile; ++i)
	{
		CCTextureCache::sharedTextureCache()->addImageAsync(picfiles[i], this, callfuncO_selector(LayerGame::loadImageCallBack));
	}
}


void LayerGame::loadImageCallBack(CCObject *)
{
	_loadFileCount ++;
	_bar->setPercentage(_loadFileCount * 100.0f / _totalfile);
	if (_loadFileCount == _totalfile)
	{
		_bar->removeFromParent();
		startGame();
	}
}

void LayerGame::moveMario(float dt)
{ 
	if (_mario->_autoRun) return;
#ifdef WIN32
	if (GetKeyState('A') < 0)  _marioDir = Common::LEFT;
	else if (GetKeyState('D') < 0) _marioDir = Common::RIGHT;
	if (GetKeyState('J') < 0) _mario->jump();
#endif // WIN32
	switch (_marioDir)
	{
	case Common::LEFT:
		_marioDir = Common::NONE;
		_mario->moveLeft(dt);
		break;
	case Common::RIGHT:
		_marioDir = Common::NONE;
		_mario->moveRight(dt);
		break;
	case Common::UP:
	case Common::DOWN:
	case Common::NONE:
		_menuShow->setTexture(this->_textureDirNone);
		_mario->stop();
		break;
	default:
		break;
	}
	_mario->moveUp(dt);
	_mario->moveDown(dt);
}

void LayerGame::startGame()
{
	// 加载地图
	_map = CCTMXTiledMap::create(Common::format(_idx + 1, "MarioMap", ".tmx"));
	addChild(_map);
	// 在libcocos2d项目中ccConfig.h CC_LABELBMFONT_DEBUG_DRAW修改为1可防止黑线
	// 防地图抖动
	CCArray *pChildrenArray = _map->getChildren();
	CCSpriteBatchNode *child = NULL;
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(pChildrenArray, pObject){
		child = (CCSpriteBatchNode *)pObject;
		if (!child)
			break;
		child->getTexture()->setAntiAliasTexParameters();
	}

	Common::moveNode(_map, ccp(0, winSize.height - _map->getContentSize().height));
	// 加载蘑菇怪资源
	{
		CCAnimation * animation = Common::CreateAnimation("Mushroom0.png", 0, 1, 16, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, IT_MUSHROOM_MOVING_ANIMATE_NAME);
		CCSpriteFrame * dead1 = Common::getSpriteFrame("Mushroom0.png", 2, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(dead1, IT_MUSHROOM_DEAD1_NAME);
		CCSpriteFrame * dead2 = Common::getSpriteFrame("Mushroom0.png", 3, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(dead2, IT_MUSHROOM_DEAD2_NAME);
	}
	// 加载乌龟资源
	{
		CCAnimation * animation1 = Common::CreateAnimation("tortoise0.png", 2, 3, 18, 0.4f);
		CCAnimation * animation2 = Common::CreateAnimation("tortoise0.png", 4, 5, 18, 0.4f);
		CCAnimation * animation3 = Common::CreateAnimation("tortoise0.png", 8, 9, 18, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, IT_TORTOISE_MOVING_LEFT_ANIMATE_NAME);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, IT_TORTOISE_MOVING_RIGHT_ANIMATE_NAME);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation3, IT_TORTOISE_DEAD);

		CCAnimation * animation4 = Common::CreateAnimation("tortoise0.png", 0, 1, 18, 0.4f);
		CCAnimation * animation5 = Common::CreateAnimation("tortoise0.png", 6, 7, 18, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation4, IT_TORTOISE_FLY_LEFT_ANIMATE_NAME);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation5, IT_TORTOISE_FLY_RIGHT_ANIMATE_NAME);
	}
	// 增加剪刀花资源
	{
		CCAnimation * animation = Common::CreateAnimation("flower0.png", 0, 1, 16, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, IT_FLOWER_SHOW);
	}
	// MushroomReward
	{
		CCSpriteFrame * frame = Common::getSpriteFrame("rewardMushroomSet.png", 0, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, IT_MUSHROOM_REWARD);
	}
	// MushroomAddLife
	{
		CCSpriteFrame * frame = Common::getSpriteFrame("rewardMushroomSet.png", 1, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, IT_MUSHROOM_ADD_LIFE);
	}

	// FlyFish
	{
		CCAnimation * animation1 = Common::CreateAnimation("flyFishLeft.png", 0, 5, 16, 0.05f);
		CCAnimation * animation2 = Common::CreateAnimation("flyFishRight.png", 0, 5, 16, 0.05f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, IT_FLY_FISH_LEFT);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, IT_FLY_FISH_RIGHT);
	}
	// BOSS
	{
		CCAnimation * animation1 = Common::CreateAnimation("boss.png", 0, 3, 32, 0.05f);
		CCAnimation * animation2 = Common::CreateAnimation("boss.png", 4, 7, 32, 0.05f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, IT_BOSS_WALK_LEFT);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, IT_BOSS_WALK_RIGHT);
	}
	// BOSS Bullet动画
	{
		CCAnimation * animation1 = Common::CreateAnimation("bossBullet.png", 0, 1, 24, 0.05f);
		CCAnimation * animation2 = Common::CreateAnimation("bossBullet.png", 2, 3, 24, 0.05f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, IT_BOSS_BULLET_LEFT);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, IT_BOSS_BULLET_RIGHT);
	}
	// 增加控制按钮
	addCtrl();

	// 移动马里奥
	schedule(schedule_selector(LayerGame::moveMario));

	// 额，奖赏蘑菇初始化
	if (Item::m_arrItemReward != NULL)
	{
		Item::m_arrItemReward->release();
	}
	Item::m_arrItemReward = CCArray::create();
	Item::m_arrItemReward->retain();

	// 加载地图对象元素
	CCTMXObjectGroup * objGroup = _map->objectGroupNamed("objects");
	CCArray * objs = objGroup->getObjects();
	// 创建Mario
	_mario = Mario::create();

	Item::m_bridge = NULL;

	CCObject * obj;
	CCARRAY_FOREACH(objs, obj)
	{
		CCDictionary * dict = (CCDictionary *)obj;
		const CCString * x = dict->valueForKey("x");
		const CCString * y = dict->valueForKey("y");
		const CCString * type = dict->valueForKey("type");
		if (type->m_sString == "BirthPoint")
		{
			// mario
			_mario->setPosition(ccp(x->intValue(), y->intValue() - _map->getTileSize().height));
			_mario->setAnchorPoint(ccp(0, 0));
			_map->addChild(_mario);
		}
		else
		{
			Item * item = Item::create(dict);
			if (item != NULL)
			{
				item->_mario = _mario;
				//_items->addObject(item);
				_map->addChild(item);
			}
		}
	}

	schedule(schedule_selector(LayerGame::checkMarioDie));
	//  启动定时器来检测mario是否碰到旗杆
	schedule(schedule_selector(LayerGame::checkMarioTouchPole));
	// 吃金币定时器
	schedule(schedule_selector(LayerGame::eatCoin));
	if (Mario::_life == 0) Mario::_life = 3;
}

void LayerGame::eatCoin(float)
{
	CCRect rc = _mario->boundingBox();
	if (rc.getMaxY() > _map->getContentSize().height || rc.getMinY() < 0) return;
	CCTMXLayer * coinLayer = _map->layerNamed("coin");
	CCPoint pt[4];
	pt[0] = ccp(rc.getMinX(), rc.getMinY());
	pt[1] = ccp(rc.getMinX(), rc.getMaxY());
	pt[2] = ccp(rc.getMaxX(), rc.getMinY());
	pt[3] = ccp(rc.getMaxX(), rc.getMaxY());

	for (int i = 0; i < 4; ++i)
	{
		CCPoint ptTile = Common::Point2Tile(_map, pt[i]);
		int gid = coinLayer->tileGIDAt(ptTile);
		if (gid != 0)
		{
			// 播放吃金币的声音
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EatCoin.wma");
			coinLayer->setTileGID(0, ptTile);
		}
	}
}

void LayerGame::checkMarioTouchPole(float)
{
	CCRect rcMario = _mario->boundingBox();
	CCPoint pt = ccp(rcMario.getMaxX() - 8, rcMario.getMaxY());
	CCPoint ptInMap = Common::Point2Tile(_map, pt);
	CCTMXLayer * layer = _map->layerNamed("flagpole");

	if (ptInMap.y < 0 || ptInMap.y > _map->getMapSize().height) return;


	// 碰到旗杆了
	if (layer->tileGIDAt(ptInMap) != 0)
	{
		_mario->autoRun();
		unschedule(schedule_selector(LayerGame::checkMarioTouchPole));
	}
}

void LayerGame::checkMarioDie(float)
{
	CCRect rc = _mario->boundingBox();
	if (rc.getMaxY() < 0)
		GameOver();
}

void LayerGame::addCtrl()
{
	// 控制按钮背景图
	CCSprite * sprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("controlUI.png"));
	addChild(sprite);
	sprite->setPosition(ccp(0, 0));
	sprite->setAnchorPoint(ccp(0, 0));
	
	// 显示在菜单位置的纹理
	_textureDirNone = CCTextureCache::sharedTextureCache()->addImage("backKeyImage.png");
	_textureDirLeft = CCTextureCache::sharedTextureCache()->addImage("backKeyLeft.png");
	_textureDirRight = CCTextureCache::sharedTextureCache()->addImage("backKeyRight.png");

	_menuShow = CCSprite::createWithTexture(_textureDirNone);
	addChild(_menuShow);
	CCPoint ptmenuShowPos = ccp(70, 50);
	_menuShow->setPosition(ptmenuShowPos);

	// 定制菜单，每个桢循环都会触发的菜单
	// 菜单项是透明的，菜单的养生由别的精灵来显示
	MenuCtrl * menu = MenuCtrl::create();
	addChild(menu);

	CCSprite * left1 = NULL, * left2 = NULL, * right1 = NULL, * right2 = NULL;
	left1 = CCSprite::create();
	left2 = CCSprite::create();
	right1 = CCSprite::create();
	right2 = CCSprite::create();
	CCSize dSize = CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height);
	left1->setContentSize(dSize);
	left2->setContentSize(dSize);
	right1->setContentSize(dSize);
	right2->setContentSize(dSize);
	CCMenuItemSprite * left = CCMenuItemSprite::create(left1, left2, this, menu_selector(LayerGame::moveLeft));
	CCMenuItemSprite * right = CCMenuItemSprite::create(right1, right2, this, menu_selector(LayerGame::moveRight));
	menu->addChild(left);
	menu->addChild(right);

	left->setPosition(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2);
	right->setPosition(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2);
	Common::moveNode(left, ccp(-_menuShow->getContentSize().width / 4, 0));
	Common::moveNode(right, ccp(_menuShow->getContentSize().width / 4, 0));

	_marioDir = Common::NONE;

	// 跳跃，发射子弹，弹窗
	addJumpFireMenuCtrl();
}
void LayerGame::addJumpFireMenuCtrl()
{
	// 创建菜单
	CCMenu * menu = CCMenu::create();
	addChild(menu);
	// 创建跳跃按钮
	CCTexture2D * textureABNormal = CCTextureCache::sharedTextureCache()->addImage("AB_normal.png");
	CCTexture2D * textureABSelect = CCTextureCache::sharedTextureCache()->addImage("AB_select.png");
	CCSprite * jumpNormal = CCSprite::createWithTexture(textureABNormal);
	CCSprite * jumpSelect = CCSprite::createWithTexture(textureABSelect);
	CCMenuItemSprite * jump = CCMenuItemSprite::create(jumpNormal, jumpSelect, this, menu_selector(LayerGame::Jump));
	menu->addChild(jump);
	Common::moveNode(jump, ccp(190, -125));
}

void LayerGame::Jump(CCObject *)
{
	if (_mario->_autoRun) return;
	_mario->jump();
}

void LayerGame::moveLeft(CCObject *)
{
	_menuShow->setTexture(this->_textureDirLeft);
	_marioDir = Common::LEFT;
}

void LayerGame::moveRight(CCObject *)
{
	_menuShow->setTexture(this->_textureDirRight);
	_marioDir = Common::RIGHT;
}

void LayerGame::GameOver()
{
	Mario::_life -= 1;
	if (Mario::_life == 0)
		CCDirector::sharedDirector()->replaceScene(Common::scene(LayerStart::create()));
	else
		CCDirector::sharedDirector()->replaceScene(Common::scene(LayerGame::create(_idx)));
		//CCDirector::sharedDirector()->replaceScene(Common::scene(LayerMenu::create()));
}