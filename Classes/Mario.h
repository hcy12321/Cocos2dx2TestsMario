#ifndef __MARIO_H__
#define __MARIO_H__

#include "Common.h"
#include "Item.h"
// mario对象
class Mario:public CCSprite
{
public:
	CREATE_FUNC(Mario);
	bool init();
	void onExit();

	CCTMXTiledMap * getMap();
	// 水平运动的操作函数
	void moveDir(float dt, Common::DIRECTON dir);
	void moveLeft(float dt);
	void moveRight(float dt);
	// 根据状态，修改mario的表现形式
	void updateStatus();
	void stop();
	// 移动控制
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);
	bool canMoveUp(float dt);
	// 竖直方向运动
	void jump();
	void moveUp(float dt);
	void moveDown(float dt);
	void bounce();

	void Die(bool dead = true);
	void Hit(const std::string& layername, int gid, CCPoint ptTile);
	void wakeupMushroomReward(CCNode *);
	void eatMushroom(Item::ItemType type);
	void setGodMode(int time);
	void unsetGodMode(float);
	void Dead();
	void autoRun();
	void autoRun2();
	void walkForward(float dt);

	// status
	Common::DIRECTON _dirRun; // LEFT, RIGHT, NONE
	Common::DIRECTON _dirFace; // LEFT, RIGHT
	int _speedUp; // 向上的速度，如果速度不为0，说明 mario要上升
	int _speedDown; // 向下的速度
	int _speedAcc; // g
	static int _life;		// 命
	bool _canFire;	// 是否有子弹
	bool _isBig;	// 是否变大
	int _speed;		// 速度
	bool _bFly; // 是不是在空中
	bool _bGodMode; // 无敌模式
	bool _dead;	// 死了
	bool _autoRun; // 自动走
	bool _flagRunAction; // 旗子下降标志
	bool _onLadder; // 梯子上

	

};
#endif // !__MARIO_H__



