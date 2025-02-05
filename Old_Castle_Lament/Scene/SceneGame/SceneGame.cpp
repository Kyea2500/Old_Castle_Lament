#include "SceneGame.h"
#include<math.h>
#include"../../GameProcess/Game.h"
#include <DxLib.h>
#include "../../GameProcess/Pad/Pad.h"
namespace
{
	constexpr int NextScene = 30;
	const int Color = GetColor(20, 20, 40);
}

SceneGame::SceneGame():
	HitPlayer(false),
	HitBoss(false),
	HitBat(false),
	HitEye(false),
	HitShot(false),
	m_isGameEnd(false),
	isHitPlayerToEnemy(false),
	isHitShotToEnemy(false),
	ChangeCount(0)
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
SceneManager::SceneKind SceneGame::Update()
{
	if (m_isGameEnd)
	{
		ChangeCount++;
		if (ChangeCount >= NextScene)
		{
			if (player.GetLife() == 0)
			{
				return SceneManager::SceneKind::kSceneGameOver;
			}
			else
			{
				return SceneManager::SceneKind::kSceneGameClear;
			}
		}
	}
	player.Update();
	boss.Update();
	bat.Update();
	eye.Update();

	//オブジェクト間の当たり判定
	ObjectCol();

	//弾との当たり判定
	BulletCol();

	if (player.GetLife() == 0)
	{
			m_isGameEnd = true;
	}
	else if (boss.GetLife() == 0)
	{
		m_isGameEnd = true;
	}
	return SceneManager::kSceneGame;

}

void SceneGame::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color, true);
#ifdef DISP_COLLISION
	DrawLineAA(Game::kScreenWidth / 3.18f, 0.0f, Game::kScreenWidth / 3.2f, Game::kScreenHeight, GetColor(255, 255, 255));    // 射撃可能エリア
	DrawLineAA(Game::kScreenWidth / 2 - 32 * 1.5 / 2, 0.0f, Game::kScreenWidth / 2 - 32 * 1.5 / 2, Game::kScreenHeight, GetColor(0, 255, 255));    // 操作可能エリア
#endif
	boss.Draw();
	player.Draw();
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

void SceneGame::ObjectCol()
{
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

	// プレイヤーと敵が衝突するとプレイヤーにダメージが入る
	if (PtoB <= player.Player_HitCircleRad() + boss.Boss_AttackCircleRad())
	{
		HitPlayer = true;
#ifdef DISP_COLLISION
		DrawString(0, 20, L"hitPlayer", 0xffffff);
#endif
	}
	else if (Ptob <= player.Player_HitCircleRad() + bat.Bat_HitCircleRad())
	{
		HitPlayer = true;
		bat.OnDamage();
#ifdef DISP_COLLISION
		DrawString(0, 20, L"hitPlayer", 0xffffff);
#endif
	}
	else if (PtoE <= player.Player_HitCircleRad() + eye.Eye_HitCircleRad())
	{
		HitPlayer = true;
		eye.OnDamage();
#ifdef DISP_COLLISION
		DrawString(0, 20, L"hitPlayer", 0xffffff);
#endif
	}
	else
	{
		HitPlayer = false;
	}

#ifdef DISP_COLLISION
	//Playerと敵の相対距離
	DrawFormatString(0, 40, 0xffffff, L"PtoBLength:%f", PtoB);
	DrawFormatString(0, 60, 0xffffff, L"PtobLength:%f", Ptob);
	DrawFormatString(0, 80, 0xffffff, L"PtoELength:%f", PtoE);
#endif

	//エネミーとプレイヤーが当たったかどうかの判定
	if (HitPlayer)
	{
		player.OnDamage();
	}
}

void SceneGame::BulletCol()
{
	/*ボス*/
	// 弾とボスの当たり判定
	float StoB_X = player.Shot_CircleX() - boss.Boss_HitCircleX();
	float StoB_Y = player.Shot_CircleY() - boss.Boss_HitCircleY();
	float StoB = sqrt(StoB_X * StoB_X + StoB_Y * StoB_Y);

#ifdef DISP_COLLISION
	//弾とボスの相対位置
	DrawFormatString(0, 100, 0xffffff, L"StoBLength:%f", StoB);
	DrawFormatString(0, 160, 0xffffff, L"PtoBRad:%f", player.Player_HitCircleRad() + boss.Boss_HitCircleRad());
#endif

	// 弾が敵に当たると弾が消滅し、ダメージを与える
	if (StoB <= player.Shot_CircleRad() + boss.Boss_HitCircleRad())
	{
		player.HitShot();
		boss.OnDamage();
#ifdef DISP_COLLISION
		DrawString(0, 0, L"hitBoss", 0xffffff);
#endif
	}
	else// 当たらなければ変化しない
	{
		HitShot = false;
	}

	// 弾とボスの攻撃との当たり判定
	float StoA_X = player.Shot_CircleX() - boss.Boss_AttackCircleX();//
	float StoA_Y = player.Shot_CircleY() - boss.Boss_AttackCircleY();
	float StoA = sqrt(StoA_X * StoA_X + StoA_Y * StoA_Y);

	// 弾が敵に当たると弾が消滅し、ダメージを与える
	if (StoA <= player.Shot_CircleRad() + boss.Boss_AttackCircleRad())
	{
		player.HitShot();
#ifdef DISP_COLLISION
		DrawString(0, 0, L"DeleteShot", 0xffffff);
#endif
	}
	else// 当たらなければ変化しない
	{
		HitShot = false;

	}

	/*コウモリ*/
	// 弾とコウモリの当たり判定
	float Stob_X = player.Shot_CircleX() - bat.Bat_HitCircleX();
	float Stob_Y = player.Shot_CircleY() - bat.Bat_HitCircleY();
	float Stob = sqrt(Stob_X * Stob_X + Stob_Y * Stob_Y);

#ifdef DISP_COLLISION
	//弾とコウモリの相対位置
	DrawFormatString(0, 120, 0xffffff, L"StobLength:%f", StoB);
	DrawFormatString(0, 180, 0xffffff, L"PtobRad:%f", player.Player_HitCircleRad() + bat.Bat_HitCircleRad());
#endif

	if (Stob <= player.Shot_CircleRad() + bat.Bat_HitCircleRad())
	{
		player.HitShot();
		bat.OnDamage();
#ifdef DISP_COLLISION
		DrawString(0, 0, L"hitBat", 0xffffff);
#endif
	}
	else// 当たらなければ変化しない
	{
		HitShot = false;
	}

	/*目玉*/
	// 弾と目玉の当たり判定
	float StoE_X = player.Shot_CircleX() - eye.Eye_HitCircleX();
	float StoE_Y = player.Shot_CircleY() - eye.Eye_HitCircleY();
	float StoE = sqrt(StoE_X * StoE_X + StoE_Y * StoE_Y);

#ifdef DISP_COLLISION
	//弾と目玉の相対位置
	DrawFormatString(0, 140, 0xffffff, L"StoELength:%f", StoB);
	DrawFormatString(0, 200, 0xffffff, L"PtoERad:%f", player.Player_HitCircleRad() + bat.Bat_HitCircleRad());
#endif

	if (StoE <= player.Shot_CircleRad() + eye.Eye_HitCircleRad())
	{
		player.HitShot();
		eye.OnDamage();
#ifdef DISP_COLLISION
		DrawString(0, 0, L"hitEye", 0xffffff);
#endif
	}
	else
	{
		HitShot = false;
	}

}