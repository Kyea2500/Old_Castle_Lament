#include "Boss.h"
#include"../プロジェクトに追加すべきファイル_VC用/DxLib.h"
#include"../../../GameProcess/Game.h"
#include"../Bat/Bat.h"
#include"../Eye/Eye.h"
#include <random>

namespace
{
	// ボスのキャラクターグラフィックの幅と高さ
	constexpr int kBossGraphWidth = 120;
	constexpr int kBossGraphHeight = 120;
	constexpr int kBossGraphSize = 120;

	constexpr float B_CicleX = kBossGraphWidth * 2.5f;
	constexpr float B_CicleY = kBossGraphHeight * 2;
	constexpr float B_CicleR = kBossGraphSize / 1.5f;

	constexpr float B_AttackX = kBossGraphWidth;
	constexpr float B_AttackY = kBossGraphHeight;
	constexpr float B_AttackR = kBossGraphSize;

	constexpr float AttackSpeed = 25.0f;

	// ボスのアニメーションコマ数
	constexpr int kBossIdleAnimNum = 6;
	constexpr int kBoaaSpawnAnimNum = 11;
	constexpr int kBossWalkAnimNum = 6;
	constexpr int kBossAttackAnimNum = 15;
	constexpr int kBossDeadAnimNum = 5;

	// ボスのX軸Y軸
	constexpr float kBossPosX = Game::kScreenWidth / 2;
	constexpr float kBossPosY = Game::kScreenHeight - 85.0f;

	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 18;
	constexpr int kAttackFrame = 162;

	constexpr int kDamageBlinkFrame = 20;
}
Boss::Boss():
	BossSpawn(-1),
	BossIdle(-1),
	BossWalk(-1),
	BossAttack(-1),
	/*BossShot(-1),*/
	BossDead(-1),
	Boss_pos(kBossPosX, kBossPosY),
	AttackPos(Game::kScreenWidth / 2,Game::kScreenHeight / 2- kBossGraphSize),
	Boss_animFrame(0),
	Boss_AttackFrame(0),
	BossLife(1),
	BossBlinkFrameCount(0),
	BossIsSpawn(false),
	BossIsIdle(false),
	BossIsWalk(false),
	BossIsAttack(false),
	Boss_isNext(-1),
	BossDamageFlag(false)
{
}

Boss::~Boss()
{
}

void Boss::Init()
{
	BossSpawn= LoadGraph(L"../date/image/skeleton_seeker_Spawn.png");
	BossIdle = LoadGraph(L"../date/image/skeleton_seeker_Idle.png");
	BossWalk = LoadGraph(L"../date/image/skeleton_seeker_Walk.png");
	BossAttack = LoadGraph(L"../date/image/skeleton_seeker_Attack.png");
	/*BossShot = LoadGraph(L"../date/image/skeleton_seeker_Shot.png");*/
	BossDead = LoadGraph(L"../date/image/skeleton_seeker_Death.png");
	BossLife = BOSS_LIFE;
	
}

float Boss::Boss_HitCircleX()
{
	return Boss_pos.x+ B_CicleX;
}

float Boss::Boss_HitCircleY()
{
	return Boss_pos.y - B_CicleY;
}

float Boss::Boss_HitCircleRad()
{
	return  B_CicleR;
}

// 攻撃の判定
float Boss::Boss_AttackCircleX()
{
	return AttackPos.x- B_AttackX;
}

float Boss::Boss_AttackCircleY()
{
	return AttackPos.y;
}

float Boss::Boss_AttackCircleRad()
{
	return B_AttackR;
}

// 敵の弾の当たり判定
float Boss::Boss_ShotCircleX()
{
	return 0.0f;
}

float Boss::Boss_ShotCircleY()
{
	return 0.0f;
}

float Boss::Boss_ShotCircleRad()
{
	return 0.0f;
}

void Boss::Update()
{
	Boss_animFrame++;
	// アニメーションの全体数
	int totalFrame = kBoaaSpawnAnimNum * kSingleAnimFrame;

	if (BossIsIdle)
	{
		
		totalFrame = kBossIdleAnimNum * kSingleAnimFrame;
	}
	if (BossIsWalk)
	{
		
		totalFrame = kBossWalkAnimNum * kSingleAnimFrame;
	}
	if (BossIsAttack)
	{
		Boss_AttackFrame++;
		totalFrame = kBossAttackAnimNum * kSingleAnimFrame;
		if (Boss_AttackFrame >= kAttackFrame)
		{
			AttackPos.y += AttackSpeed;
		}
	}


	if (Boss_animFrame >= totalFrame)
	{
		Boss_AttackFrame = 0;
		if (BossLife > 0)
		{
			Boss_isNext = GetRand(3);
			if (Boss_isNext > 2)
			{
				Boss_isNext = 0;
			}

			if (BossIsSpawn)
			{
				BossIsSpawn = false;
				Boss_animFrame = 0;
			}

			if (BossIsIdle)
			{
				BossIsIdle = false;
				Boss_animFrame = 0;
			}
			if (BossIsWalk)
			{

				BossIsWalk = false;
				Boss_animFrame = 0;
			}
			if (BossIsAttack)
			{
				BossIsAttack = false;
				Boss_animFrame = 0;
			}
			/*if (BossIsShot)
			{
				BossIsShot = false;
				Boss_animFrame = 0;
			}*/

			UpdateSpawn();
			UpdateIdle();
			UpdateMove();
			UpdateAttack();
			//UpdateShot();
			
		}
		if (BossLife == 0)
		{
			UpdateDead();
		}
	}

	if (BossDamageFlag)
	{
		BossBlinkFrameCount--;
		if (BossBlinkFrameCount <= 0)
		{
			BossDamageFlag = false;
		}
	}

	if (CheckHitKey(KEY_INPUT_O))
	{
		OnDamage();
	}

	if (CheckHitKey(KEY_INPUT_P))
	{
		Boss_animFrame = 0;
		BossLife = 0;
	}
}

void Boss::Draw()
{
	// 点滅処理
	if ((BossBlinkFrameCount / 2) % 2)
	{
		return;
	}
	int useHandle = BossSpawn;

	if (BossIsIdle)
	{
		useHandle = BossIdle;
	}
	if (BossIsWalk)
	{
		useHandle = BossWalk;
	}
	if (BossIsAttack)
	{
		useHandle = BossAttack;
	}
	/*if (BossIsShot)
	{
		useHandle = BossShot;
	}*/

	int animNo = Boss_animFrame / kSingleAnimFrame;
	if (BossLife >0)
	{
		DrawRectRotaGraph(static_cast<int>(Boss_pos.x + kBossGraphWidth * 3), static_cast<int>(Boss_pos.y - kBossGraphHeight),
			0, animNo * kBossGraphHeight, kBossGraphWidth, kBossGraphHeight, 10.0f, 0,
			useHandle, true, true, false);
	}

	if (BossLife == 0)
	{
		DrawRectRotaGraph(static_cast<int>(Boss_pos.x + kBossGraphWidth * 3), static_cast<int>(Boss_pos.y - kBossGraphHeight*3),
			0, animNo * kBossGraphHeight, kBossGraphWidth, kBossGraphHeight, 10.0f, 0,
			BossDead, true, true, false);
	}

	DrawCircle(Boss_HitCircleX(), Boss_HitCircleY(), Boss_HitCircleRad(), 0xffffff, false);
	if (BossIsAttack)
	{
		DrawCircle(Boss_AttackCircleX(), Boss_AttackCircleY(), Boss_AttackCircleRad(), 0xffffff, false);
	}
}

void Boss::OnDamage()
{
	BossDamageFlag = true;
	BossLife -= 1;
}

void Boss::End()
{
	DeleteGraph(BossSpawn);
	DeleteGraph(BossIdle);
	DeleteGraph(BossWalk);
	DeleteGraph(BossAttack);
}

void Boss::UpdateSpawn()
{
	BossIsSpawn = false;
	if (Boss_isNext < 0)
	{
		BossIsSpawn = true;
	}
}

void Boss::UpdateMove()
{
	BossIsWalk = false;
	if (Boss_isNext == 1)
	{
		BossIsWalk = true;
	}
}

void Boss::UpdateAttack()
{
	BossIsAttack = false;
	AttackPos.y = 0 - kBossGraphSize;
	if (Boss_isNext == 2)
	{
		BossIsAttack = true;
	}
}

//void Boss::UpdateShot()
//{
//}

void Boss::UpdateIdle()
{
	BossIsIdle = false;
	if (Boss_isNext == 0)
	{
		BossIsIdle = true;
	}
}

void Boss::UpdateDead()
{
	Boss_animFrame++;
	int totalFrame = kBossDeadAnimNum * kSingleAnimFrame;
	if (Boss_animFrame >= totalFrame)
	{
		return;
	}
}
