#include "Boss.h"
#include"../プロジェクトに追加すべきファイル_VC用/DxLib.h"
#include"../../../GameProcess/Game.h"

#include <random>

namespace
{
	// ボスのキャラクターグラフィックの幅と高さ
	constexpr int kBossGraphWidth = 120;
	constexpr int kBossGraphHeight = 120;
	constexpr int kBossGraphSize = 120;
	constexpr float ChangeSize = 10.0f;

	constexpr int kShotGraphWidth = 64;
	constexpr int kShotGraphHeight = 64;
	constexpr int kShotGraphSize = 64;

	constexpr float B_CicleX = kBossGraphWidth * 2.5f;
	constexpr float B_CicleY = kBossGraphHeight * 2;
	constexpr float B_CicleR = kBossGraphSize / 1.5f;

	constexpr float B_AttackX = kBossGraphWidth;
	constexpr float B_AttackY = kBossGraphHeight;
	constexpr float B_AttackR = kBossGraphSize;

	constexpr float B_ShotX = kShotGraphWidth * 2;
	constexpr float B_ShotY = kShotGraphHeight * 2;
	constexpr float B_ShotR = kBossGraphSize / 2;

	constexpr float AttackSpeed = 25.0f;

	constexpr int first = 1;
	constexpr int second = 2;
	constexpr int third = 3;

	constexpr int half = 2;
	constexpr int StertX = 3;
	constexpr int StertY = 3;

	constexpr int ShotDamageIce = 3;
	constexpr int ShotDamageThunder = 2;
	constexpr int ShotDamageAir = 1;

	// ボスのアニメーションコマ数
	constexpr int kBossIdleAnimNum = 6;
	constexpr int kBoaaSpawnAnimNum = 11;
	constexpr int kBossWalkAnimNum = 6;
	constexpr int kBossAttackAnimNum = 15;
	constexpr int kBossSetAnimNum = 2;
	constexpr int kBossShotAnimNum = 5;
	constexpr int kBossDeadAnimNum = 5;

	// ボスのX軸Y軸
	constexpr float kBossPosX = Game::kScreenWidth / 2;
	constexpr float kBossPosY = Game::kScreenHeight - 85.0f;

	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 18;
	constexpr int kAttackFrame = 162;

	constexpr int kDamageBlinkFrame = 30;
}
Boss::Boss():
	BossSpawn(-1),
	BossIdle(-1),
	BossWalk(-1),
	BossAttack(-1),
	BossShot(-1),
	BossShotSet(-1),
	BossDead(-1),
	Boss_pos(kBossPosX, kBossPosY),
	AttackPos(Game::kScreenWidth / 2, Game::kScreenHeight / 2 - kBossGraphSize),
	ShotPos(0, Game::kScreenHeight),
	Boss_animFrame(0),
	Boss_AttackFrame(0),
	BossLife(1),
	BossBlinkFrameCount(0),
	BossIsSpawn(false),
	BossIsIdle(false),
	BossIsWalk(false),
	BossIsAttack(false),
	BossIsShot(false),
	BossIsSet(false),
	BossShotis(false),
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
	BossShotSet = LoadGraph(L"../date/image/skeleton_seeker_Shot2.png");
	BossShot = LoadGraph(L"../date/image/skeleton_seeker_Shot2.png");
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
	return ShotPos.x + B_ShotX;
}

float Boss::Boss_ShotCircleY()
{
	return ShotPos.y + B_ShotY;
}

float Boss::Boss_ShotCircleRad()
{
	return B_ShotR;
}

void Boss::Update()
{
	Boss_animFrame++;
	BossBlinkFrameCount--;
	if (BossBlinkFrameCount < 0)
	{
		BossBlinkFrameCount = 0;
	}
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

	if (BossIsSet)
	{
		totalFrame = kBossSetAnimNum * kSingleAnimFrame;
		ShotPos.y += AttackSpeed;
		if (Boss_animFrame >= totalFrame)
		{
			Boss_AttackFrame = 0;
			BossIsSet = false;
			BossIsShot = true;
		}
	}

	if (BossIsShot)
	{
		totalFrame = kBossShotAnimNum * kSingleAnimFrame;

		if (Boss_animFrame >= totalFrame)
		{
			Boss_AttackFrame = 0;
			BossIsShot = false;
		}
	}


	if (Boss_animFrame >= totalFrame)
	{
		Boss_AttackFrame = 0;
		if (BossLife >0)
		{
			Boss_isNext = GetRand(third);
			if (Boss_isNext > second)
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

			UpdateSpawn();
			UpdateIdle();
			UpdateMove();
			UpdateAttack();
			UpdateShot();
		}
		else
		{
			UpdateDead();
		}
	}

#ifdef DISP_COLLISION
	if (CheckHitKey(KEY_INPUT_O))
	{
		OnDamage();
	}

	if (CheckHitKey(KEY_INPUT_P))
	{
		Boss_animFrame = 0;
		BossLife = 0;
	}
#endif
}

void Boss::Draw()
{
	// 点滅処理
	if ((BossBlinkFrameCount / half) % half)
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

	int ShotHandle = BossShotSet;
	if (BossIsSet)
	{
		ShotHandle = BossShotSet;
	}
	if (BossIsShot)
	{
		ShotHandle = BossShot;
	}


	int animNo = Boss_animFrame / kSingleAnimFrame;
	if (BossLife >0)
	{
		DrawRectRotaGraph(static_cast<int>(Boss_pos.x + kBossGraphWidth * StertX), static_cast<int>(Boss_pos.y - kBossGraphHeight),
			0, animNo * kBossGraphHeight, kBossGraphWidth, kBossGraphHeight, ChangeSize, 0,
			useHandle, true, true, false);
#ifdef DISP_COLLISION
		DrawCircle(Boss_HitCircleX(), Boss_HitCircleY(), Boss_HitCircleRad(), 0xffffff, false);
#endif
	}

	if (BossLife == 0)
	{
		DrawRectRotaGraph(static_cast<int>(Boss_pos.x + kBossGraphWidth * StertX), static_cast<int>(Boss_pos.y - kBossGraphHeight* StertY),
			0, animNo * kBossGraphHeight, kBossGraphWidth, kBossGraphHeight, ChangeSize, 0,
			BossDead, true, true, false);
	}
#ifdef DISP_COLLISION
	if (BossIsAttack)
	{
		DrawCircle(Boss_AttackCircleX(), Boss_AttackCircleY(), Boss_AttackCircleRad(), 0xffffff, false);
	}
#endif

	if (BossShotis)
	{
		DrawRectRotaGraph(static_cast<int>(Boss_pos.x + kBossGraphWidth ), static_cast<int>(Boss_pos.y - kBossGraphHeight),
			0, animNo * kBossGraphHeight, kBossGraphWidth, kBossGraphHeight, 10.0f, 0,
			ShotHandle, true, true, false);
		DrawCircle(Boss_HitCircleX(), Boss_HitCircleY(), Boss_HitCircleRad(), 0xffffff, false);
	}

}

void Boss::OnDamage()
{
	if (BossBlinkFrameCount > 0) return;

	// 無敵時間(点滅する時間)を設定する
	BossBlinkFrameCount = kDamageBlinkFrame;

	// ダメージを受ける
	BossLife--;
	// HPが0以下になったら死亡演出を開始する
	if (BossLife <= 0)
	{
		UpdateDead();
	}
}

void Boss::End()
{
	DeleteGraph(BossSpawn);
	DeleteGraph(BossIdle);
	DeleteGraph(BossWalk);
	DeleteGraph(BossAttack);
	DeleteGraph(BossShot);
	DeleteGraph(BossShotSet);
	DeleteGraph(BossDead);
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
	if (Boss_isNext == first)
	{
		BossIsWalk = true;
		BossIsSet = true;
	}
}

void Boss::UpdateAttack()
{
	BossIsAttack = false;
	AttackPos.y = 0 - kBossGraphSize;
	if (Boss_isNext == second)
	{
		BossIsAttack = true;
	}
}

void Boss::UpdateShot()
{
	BossShotis = false;
	BossIsSet = false;
	if (BossIsSet)
	{
		BossIsSet = true;
	}
}

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
