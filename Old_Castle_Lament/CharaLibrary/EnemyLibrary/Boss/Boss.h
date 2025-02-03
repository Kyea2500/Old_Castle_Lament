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
	void OnDamage();	// ダメージを受けた時
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
	// フレーム数を数える
	int Boss_animFrame;
	int Boss_AttackFrame;
	// ボスの耐久力
	int	BossLife;
	// 点滅処理
	int BossBlinkFrameCount;
	// 待機
	bool BossIsIdle;
	// 歩く
	bool BossIsWalk;
	// 近接攻撃	
	bool BossIsAttack;
	// 遠距離攻撃
	bool BossIsSet;
	bool BossIsShot;
	bool BossShotis;
	// 出現
	bool BossIsSpawn;
	// 今はどれか
	int Boss_isNext;
	bool BossDamageFlag;
};

