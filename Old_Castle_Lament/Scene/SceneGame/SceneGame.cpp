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

	//�I�u�W�F�N�g�Ԃ̓����蔻��
	ObjectCol();

	//�e�Ƃ̓����蔻��
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
	DrawLineAA(Game::kScreenWidth / 3.18f, 0.0f, Game::kScreenWidth / 3.2f, Game::kScreenHeight, GetColor(255, 255, 255));    // �ˌ��\�G���A
	DrawLineAA(Game::kScreenWidth / 2 - 32 * 1.5 / 2, 0.0f, Game::kScreenWidth / 2 - 32 * 1.5 / 2, Game::kScreenHeight, GetColor(0, 255, 255));    // ����\�G���A
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
	// �v���C���[�ƃ{�X�̏Փ˔���
	float PtoB_X = player.Player_HitCircleX() - boss.Boss_AttackCircleX();
	float PtoB_Y = player.Player_HitCircleY() - boss.Boss_AttackCircleY();
	float PtoB = sqrt(PtoB_X * PtoB_X + PtoB_Y * PtoB_Y);

	// �v���C���[�ƃR�E�����̏Փ˔���
	float Ptob_X = player.Player_HitCircleX() - bat.Bat_HitCircleX();
	float Ptob_Y = player.Player_HitCircleY() - bat.Bat_HitCircleY();
	float Ptob = sqrt(Ptob_X * Ptob_X + Ptob_Y * Ptob_Y);

	// �v���C���[�ƃC�r���A�C�̏Փ˔���
	float PtoE_X = player.Player_HitCircleX() - eye.Eye_HitCircleX();
	float PtoE_Y = player.Player_HitCircleY() - eye.Eye_HitCircleY();
	float PtoE = sqrt(PtoE_X * PtoE_X + PtoE_Y * PtoE_Y);

	// �v���C���[�ƓG���Փ˂���ƃv���C���[�Ƀ_���[�W������
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
	//Player�ƓG�̑��΋���
	DrawFormatString(0, 40, 0xffffff, L"PtoBLength:%f", PtoB);
	DrawFormatString(0, 60, 0xffffff, L"PtobLength:%f", Ptob);
	DrawFormatString(0, 80, 0xffffff, L"PtoELength:%f", PtoE);
#endif

	//�G�l�~�[�ƃv���C���[�������������ǂ����̔���
	if (HitPlayer)
	{
		player.OnDamage();
	}
}

void SceneGame::BulletCol()
{
	/*�{�X*/
	// �e�ƃ{�X�̓����蔻��
	float StoB_X = player.Shot_CircleX() - boss.Boss_HitCircleX();
	float StoB_Y = player.Shot_CircleY() - boss.Boss_HitCircleY();
	float StoB = sqrt(StoB_X * StoB_X + StoB_Y * StoB_Y);

#ifdef DISP_COLLISION
	//�e�ƃ{�X�̑��Έʒu
	DrawFormatString(0, 100, 0xffffff, L"StoBLength:%f", StoB);
	DrawFormatString(0, 160, 0xffffff, L"PtoBRad:%f", player.Player_HitCircleRad() + boss.Boss_HitCircleRad());
#endif

	// �e���G�ɓ�����ƒe�����ł��A�_���[�W��^����
	if (StoB <= player.Shot_CircleRad() + boss.Boss_HitCircleRad())
	{
		player.HitShot();
		boss.OnDamage();
#ifdef DISP_COLLISION
		DrawString(0, 0, L"hitBoss", 0xffffff);
#endif
	}
	else// ������Ȃ���Εω����Ȃ�
	{
		HitShot = false;
	}

	// �e�ƃ{�X�̍U���Ƃ̓����蔻��
	float StoA_X = player.Shot_CircleX() - boss.Boss_AttackCircleX();//
	float StoA_Y = player.Shot_CircleY() - boss.Boss_AttackCircleY();
	float StoA = sqrt(StoA_X * StoA_X + StoA_Y * StoA_Y);

	// �e���G�ɓ�����ƒe�����ł��A�_���[�W��^����
	if (StoA <= player.Shot_CircleRad() + boss.Boss_AttackCircleRad())
	{
		player.HitShot();
#ifdef DISP_COLLISION
		DrawString(0, 0, L"DeleteShot", 0xffffff);
#endif
	}
	else// ������Ȃ���Εω����Ȃ�
	{
		HitShot = false;

	}

	/*�R�E����*/
	// �e�ƃR�E�����̓����蔻��
	float Stob_X = player.Shot_CircleX() - bat.Bat_HitCircleX();
	float Stob_Y = player.Shot_CircleY() - bat.Bat_HitCircleY();
	float Stob = sqrt(Stob_X * Stob_X + Stob_Y * Stob_Y);

#ifdef DISP_COLLISION
	//�e�ƃR�E�����̑��Έʒu
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
	else// ������Ȃ���Εω����Ȃ�
	{
		HitShot = false;
	}

	/*�ڋ�*/
	// �e�Ɩڋʂ̓����蔻��
	float StoE_X = player.Shot_CircleX() - eye.Eye_HitCircleX();
	float StoE_Y = player.Shot_CircleY() - eye.Eye_HitCircleY();
	float StoE = sqrt(StoE_X * StoE_X + StoE_Y * StoE_Y);

#ifdef DISP_COLLISION
	//�e�Ɩڋʂ̑��Έʒu
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