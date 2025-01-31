#include "SceneGame.h"
#include<math.h>
#include"../../GameProcess/Game.h"
#include <DxLib.h>

SceneGame::SceneGame():
	HitPlayer(false),
	HitBoss(false),
	HitBat(false),
	HitEye(false),
	HitShot(false),
	isHitPlayerToEnemy(false),
	isHitShotToEnemy(false)
{
}

SceneGame::~SceneGame()
{
	
}

void SceneGame::Init()
{
	player.Init();
	player.InitShot();
	boss.Init();
	bat.Init();
	eye.Init();
}
////
void SceneGame::Update()
{
	player.Update();
	boss.Update();
	bat.Update();
	eye.Update();

	////	プレイヤーと敵の各種衝突判定　////
	Collision();

	// プレイヤーとボスの衝突判定
	float PtoB_X = player.Player_HitCircleX() - boss.Boss_AttackCircleX();
	float PtoB_Y = player.Player_HitCircleY() - boss.Boss_AttackCircleY();
	float PtoB = sqrt(PtoB_X * PtoB_X + PtoB_Y * PtoB_Y);

	// プレイヤーとコウモリの衝突判定
	float Ptob_X = player.Player_HitCircleX() - bat.Bat_HitCircleX();
	float Ptob_Y = player.Player_HitCircleY() - bat.Bat_HitCircleY();
	float Ptob = sqrt(Ptob_X * Ptob_X + Ptob_Y * Ptob_Y);

	// プレイヤーとイビルアイの衝突判定
	float PtoE_X = player.Player_HitCircleX() - eye.Eye_HitCircleX();
	float PtoE_Y = player.Player_HitCircleY() - eye.Eye_HitCircleY();
	float PtoE = sqrt(PtoE_X * PtoE_X + PtoE_Y * PtoE_Y);

	////	弾と敵の各種当たり判定　////

	// 弾とボスの当たり判定
	float StoB_X = player.Shot_CircleX() - boss.Boss_HitCircleX();
	float StoB_Y = player.Shot_CircleY() - boss.Boss_HitCircleY();
	float StoB = sqrt(StoB_X * StoB_X + StoB_Y * StoB_Y);

	// 弾とコウモリの当たり判定
	float Stob_X = player.Shot_CircleX() - bat.Bat_HitCircleX();
	float Stob_Y = player.Shot_CircleY() - bat.Bat_HitCircleY();
	float Stob = sqrt(Stob_X * Stob_X + Stob_Y * Stob_Y);

	// 弾とイビルアイの当たり判定
	float StoE_X = player.Shot_CircleX() - eye.Eye_HitCircleX();
	float StoE_Y = player.Shot_CircleX() - eye.Eye_HitCircleY();
	float StoE = sqrt(StoE_X * StoE_X + StoE_Y * StoE_Y);

	// プレイヤーと敵が衝突するとプレイヤーにダメージが入る
	if (PtoB <= player.Player_HitCircleRad() + boss.Boss_AttackCircleRad())
	{
		HitPlayer = true;
		isHitPlayerToEnemy = true;
	}
	if (Ptob <= player.Player_HitCircleRad() + bat.Bat_HitCircleRad())
	{
		HitPlayer = true;
		HitBat = true;
		isHitPlayerToEnemy = true;
	}
	if (PtoE <= player.Player_HitCircleRad() + eye.Eye_HitCircleRad())
	{
		HitPlayer = true;
		HitEye = true;
		isHitPlayerToEnemy = true;
	}

	// 弾が敵に当たると弾が消滅し、ダメージを与える
	if (StoB <= player.Shot_CircleRad() + boss.Boss_HitCircleRad())
	{
		HitShot = true;
		HitBoss = true;
		isHitShotToEnemy = true;
	}
	if (Stob <= player.Shot_CircleRad() + bat.Bat_HitCircleRad())
	{
		HitShot = true;
		HitBat = true;
		isHitShotToEnemy = true;
	}
	if (StoE <= player.Shot_CircleRad() + eye.Eye_HitCircleRad())
	{
		HitShot = true;
		HitEye = true;
		isHitShotToEnemy = true;
	}
	// 当たらなければ変化しない
	else
	{
		HitPlayer = false;
		HitBoss = false;
		HitBat = false;
		HitEye = false;
		isHitShotToEnemy = false;
	}

	if (HitPlayer)
	{
		player.OnDamage();
	}
	if (HitBoss)
	{
		boss.OnDamage();
	}
	if (HitBat)
	{
		bat.OnDamage();
	}
	if (HitEye)
	{
		eye.OnDamage();
	}

	if (isHitShotToEnemy)
	{
		DrawString(0, 0, L"hitEnemy", 0xffffff);
	}

	if (isHitPlayerToEnemy)
	{
		DrawString(0, 20, L"hitPlayer", 0xffffff);
	}

	DrawFormatString(0, 40, 0xffffff, L"PtoBLength:%f", PtoB);
	DrawFormatString(0, 60, 0xffffff, L"PtobLength:%f", Ptob);
	DrawFormatString(0, 80, 0xffffff, L"PtoELength:%f", PtoE);

	DrawFormatString(0, 100, 0xffffff, L"StoBLength:%f", StoB);
	DrawFormatString(0, 120, 0xffffff, L"StobLength:%f", Stob);
	DrawFormatString(0, 140, 0xffffff, L"StoELength:%f", StoE);

	DrawFormatString(0, 160, 0xffffff, L"PtoBRad:%f", player.Player_HitCircleRad() + boss.Boss_AttackCircleRad());
	DrawFormatString(0, 180, 0xffffff, L"PtobRad:%f", player.Player_HitCircleRad() + bat.Bat_HitCircleRad());
	DrawFormatString(0, 200, 0xffffff, L"PtoERad:%f", player.Player_HitCircleRad() + eye.Eye_HitCircleRad());


	if (Ptob <= player.Player_HitCircleRad() + bat.Bat_HitCircleRad() ||
		PtoB <= player.Player_HitCircleRad() + boss.Boss_AttackCircleRad() ||
		PtoE <= player.Player_HitCircleRad() + eye.Eye_HitCircleRad())
	{
		isHitPlayerToEnemy = true;
	}

	if (StoB <= player.Shot_CircleRad() + boss.Boss_HitCircleRad() ||
		Stob <= player.Shot_CircleRad() + bat.Bat_HitCircleRad() ||
		StoE <= player.Shot_CircleRad() + eye.Eye_HitCircleRad())
	{
		isHitShotToEnemy = true;
	}


	else
	{
		isHitPlayerToEnemy = false;
		isHitShotToEnemy = false;
	}
	/*return SceneManager::SceneKind::kSceneGame;*/
}

void SceneGame::Draw()
{
	player.Draw();
	boss.Draw();
	bat.Draw();
	eye.Draw();
	
}

void SceneGame::End()
{
	player.End();
	boss.End();
	bat.End();
	eye.End();
}

void SceneGame::Collision()
{
}
