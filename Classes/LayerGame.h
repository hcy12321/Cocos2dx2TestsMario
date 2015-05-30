#ifndef __LAYERGAME_H__
#define __LAYERGAME_H__

#include "Common.h"
#include "ProgressBar.h"
#include "Mario.h"
// ÓÎÏ·Âß¼­Àà
class LayerGame : public CCLayer
{
public:
	//CREATE_FUNC(LayerGame);
	static LayerGame * create(int idx);
	bool init(int idx);
	void update(float delta);
	void onEnter();
	void onExit();

	static void GameOver();

	void loadResource();
	void startGame();
	void addCtrl();
	void addJumpFireMenuCtrl();

	void loadImageCallBack(CCObject *);
	void moveLeft(CCObject *);
	void moveRight(CCObject *);
	void moveMario(float);
	void checkMarioDie(float);
	void checkMarioTouchPole(float);

	void Jump(CCObject *);

	ProgressBar * _bar;
	CCTMXTiledMap * _map;
	Mario * _mario;
	//CCArray * _items;

	Common::DIRECTON _marioDir;

	int _totalfile;
	int _loadFileCount;
	static int _idx;
	
	CCTexture2D * _textureDirNone;
	CCTexture2D * _textureDirLeft;
	CCTexture2D * _textureDirRight;
	CCSprite * _menuShow;
	
};
#endif // !__LAYERGAME_H__

