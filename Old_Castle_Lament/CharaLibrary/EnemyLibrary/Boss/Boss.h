#pragma once
#include "../../../Vec2/Vec2.h"
class Bat;
class Eye;
class Boss
{
public:
	Boss();
	~Boss();
	void Init();
	float Boss_HitCircleX();
	float Boss_HitCircleY();
	float Boss_HitCircleRad();

	float Boss_AttackCircleX();
	float Boss_AttackCircleY();
	float Boss_AttackCircleRad();

	float Boss_ShotCircleX();
	float Boss_ShotCircleY();
	float Boss_ShotCircleRad();

	void Update();
	void UpdateMove();
	void UpdateAttack();
	void UpdateShot();
	void Draw();
	void OnDamage();	// �_���[�W���󂯂���
	void End();
private:
	void UpdateSpawn();
	void UpdateIdle();
	void UpdateDead();

	int BossSpawn;
	int BossIdle;
	int BossWalk;
	int BossAttack;
	int BossShotSet;
	int BossShot;
	int BossDead;
	Vec2 Boss_pos;
	Vec2 AttackPos;
	Vec2 ShotPos;
	// �t���[�����𐔂���
	int Boss_animFrame;
	int Boss_AttackFrame;
	// �{�X�̑ϋv��
	int	BossLife;
	// �_�ŏ���
	int BossBlinkFrameCount;
	// �ҋ@
	bool BossIsIdle;
	// ����
	bool BossIsWalk;
	// �ߐڍU��	
	bool BossIsAttack;
	// �������U��
	bool BossIsSet;
	bool BossIsShot;
	bool BossShotis;
	// �o��
	bool BossIsSpawn;
	// ���͂ǂꂩ
	int Boss_isNext;
	bool BossDamageFlag;
};

