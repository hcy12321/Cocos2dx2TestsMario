#ifndef __MARIO_H__
#define __MARIO_H__

#include "Common.h"
#include "Item.h"
// mario����
class Mario:public CCSprite
{
public:
	CREATE_FUNC(Mario);
	bool init();
	void onExit();

	CCTMXTiledMap * getMap();
	// ˮƽ�˶��Ĳ�������
	void moveDir(float dt, Common::DIRECTON dir);
	void moveLeft(float dt);
	void moveRight(float dt);
	// ����״̬���޸�mario�ı�����ʽ
	void updateStatus();
	void stop();
	// �ƶ�����
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);
	bool canMoveUp(float dt);
	// ��ֱ�����˶�
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
	int _speedUp; // ���ϵ��ٶȣ�����ٶȲ�Ϊ0��˵�� marioҪ����
	int _speedDown; // ���µ��ٶ�
	int _speedAcc; // g
	static int _life;		// ��
	bool _canFire;	// �Ƿ����ӵ�
	bool _isBig;	// �Ƿ���
	int _speed;		// �ٶ�
	bool _bFly; // �ǲ����ڿ���
	bool _bGodMode; // �޵�ģʽ
	bool _dead;	// ����
	bool _autoRun; // �Զ���
	bool _flagRunAction; // �����½���־
	bool _onLadder; // ������

	

};
#endif // !__MARIO_H__



