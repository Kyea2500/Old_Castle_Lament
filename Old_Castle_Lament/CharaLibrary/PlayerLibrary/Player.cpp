#include "Player.h"
#include "../../GameProcess/Pad/Pad.h"
#include"../プロジェクトに追加すべきファイル_VC用/DxLib.h"
#include"../../GameProcess/Game.h"
namespace
{
	// キャラクターグラフィックの幅と高さ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;
	constexpr int kGraphSize = 32;

	constexpr int kGraphWidthBig = 32 * 1.5;
	constexpr int kGraphHeightBig = 32 * 1.5;

	// キャラクターの当たり判定
	constexpr float P_CircleX =  kGraphWidth / 2;
	constexpr float P_CircleY =  kGraphHeight;
	constexpr float P_CircleR = kGraphSize / 2 / 1.5;

	// 弾のグラフィックの幅と高さ
	constexpr int kShotGraphWidth = 48;
	constexpr int kShotGraphHeight = 32;
	constexpr int kShotSize = 32*1.2;

	constexpr float S_CircleX = kShotGraphWidth / 2;
	constexpr float S_CircleY = kShotGraphHeight;
	constexpr float S_CircleR = kShotSize / 3;

	// アニメーションのコマ数
	constexpr int kIdleAnimNum = 2;
	constexpr int kRunAnimNum = 8;
	constexpr int kAttackAnimNum = 8;
	constexpr int kDeadAnimNum = 8;

	constexpr int kShotIce_AnimNum = 10;
	constexpr int kShotThunder_AnimNum = 16;
	constexpr int kShotAir_AnimNum = 14;

	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 5;

	// キャラクターの移動速度
	constexpr float kSpeed = 3.0f;

	// プレイヤーの魔法(弾)の速度
	constexpr float IceShotSpeed = 6.0f;
	constexpr float ThunderShotSpeed = 9.0f;
	constexpr float AirShotSpeed = 12.0f;

	// キャラクターのX軸
	constexpr float kPosX = 320.0f;
	constexpr float kPosY = Game::kScreenHeight - 128.0f;

	// ダッシュの処理
	constexpr float kDashPower = 10.0f; // ダッシュの加速値
	constexpr float kDeceleration = 0.4f; // ダッシュの減速値

	// ダメージ食らった後の無敵時間
	constexpr int kDamageBlinkFrame = 30;

	// 死亡演出
	constexpr int kDeadStopFrame = 30;    // 死んだ瞬間に止まる時間
	constexpr float kDeadJumpSpeed = -4.0f; // 死んだあと飛び上がる初速

	// 攻撃のクールタイム(連射を抑える処理)
	constexpr float kCoolTimeAttack = 6.0f;
	constexpr float kCoolTimeChant = 120.0f;

}

Player::Player():
	m_handleIdle(-1),
	m_handleMove(-1),
	m_handleAttack(-1),
	m_handleIce_Shot(-1),
	m_handleThunder_Shot(-1),
	m_handleAir_Shot(-1),	
	m_handleLife(-1),
	m_handleDead(-1),
	m_isDead(false),
	m_pos(kPosX, kPosY),
	shot_pos(m_pos.x, m_pos.y),
	m_Life(PLAYER_LIFE),
	m_isDamage(false),
	m_isDirLeft(false),
	m_isDirRight(false),
	m_isDirUp(false),
	m_isDirDown(false),
	m_ishir(false),
	m_animFrame(0),
	m_isMove(false),
	m_isSpeed(kSpeed),
	m_isDash(false),
	m_DashSpeed(0.0f),
	m_isLastDashButton(false),
	m_isAttack(false),
	m_isShot(false),
	m_ShotBotton(false),
	m_isChange(false),
	m_isChargingFrame(0.0f),
	m_Change(0),
	m_Chant(0),
	m_blinktime(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_handleIdle = LoadGraph(L"../date/image/player_idle.png");
	m_handleMove = LoadGraph(L"../date/image/player_run.png");
	m_handleAttack = LoadGraph(L"../date/image/player_attack.png");
	m_handleDead = LoadGraph(L"../date/image/player_dead.png");
}

void Player::InitShot()
{
	m_handleIce_Shot = LoadGraph(L"../date/image/IceShot.png");
	m_handleThunder_Shot = LoadGraph(L"../date/image/ThunderShot.png");
	m_handleAir_Shot = LoadGraph(L"../date/image/AirShot.png");
}

void Player::Update()
{
	Pad::Update();
	if (!m_isDead)
	{
		UpdateNormal();
	}

	if(m_isDead)
	{
		UpdateDead();
	}

}

void Player::OnDamage()
{
	m_Life--;
	// HPが0以下になったら死亡演出を開始する
	if (m_Life <= 0)
	{
		m_isDead = true;
	}
}

float Player::Player_HitCircleX()
{
	
	return m_pos.x- P_CircleX;
}

float Player::Player_HitCircleY()
{
	return m_pos.y- P_CircleY;
}

float Player::Player_HitCircleRad()
{
	return P_CircleR;
}

float Player::Shot_CircleX()
{
	return shot_pos.x- S_CircleX;
}

float Player::Shot_CircleY()
{
	return shot_pos.y-S_CircleY;
}

float Player::Shot_CircleRad()
{
	return S_CircleR;
}

void Player::UpdateNormal()
{
	// アニメーションの更新
	m_animFrame++;
	m_blinktime--;
	if (m_blinktime <= 0)
	{
		m_blinktime = 0;
	}
	// アニメーションの全体数
	int totalFrame = kIdleAnimNum * kSingleAnimFrame;
	if (m_isMove)
	{
		totalFrame = kRunAnimNum * kSingleAnimFrame;
	}
	// アニメーションの合計フレーム数を超えたら最初に戻す
	if (m_isAttack)
	{
		totalFrame = kAttackAnimNum * kSingleAnimFrame;

		if (m_animFrame >= totalFrame)
		{
			m_animFrame = 0;
			m_isAttack = false;
		}
	}

	if (m_isChange)
	{
		totalFrame = kAttackAnimNum * kSingleAnimFrame;

		if (m_animFrame >= totalFrame)
		{
			m_animFrame = 0;
			m_isChange = false;
		}
	}

	if (m_animFrame >= totalFrame)
	{
		m_animFrame = 0;
	}
	bool isLastRun = m_isMove;


	// 移動していないとき、フラグを下ろす
	/*if (m_isDirUp == true)DrawFormatString(0, 20, 0xffffff, L"Up : true");
	if (m_isDirLeft == true)DrawFormatString(0, 40, 0xffffff, L"Left : true");
	if (m_isDirRight == true)DrawFormatString(0, 60, 0xffffff, L"Right : true");
	if (m_isDirDown == true)DrawFormatString(0, 80, 0xffffff, L"Down : true");*/
	if(m_Change==0)DrawFormatString(0,Game::kScreenHeight- kGraphHeight, 0xffffff, L"IceShot");
	if(m_Change==1)DrawFormatString(0,Game::kScreenHeight - kGraphHeight, 0xffffff, L"ThunderShot");
	if(m_Change==2)DrawFormatString(0,Game::kScreenHeight - kGraphHeight, 0xffffff, L"AirShot");

	if (m_isMove != isLastRun)
	{
		m_animFrame = 0;
	}

	// 一連の処理を行った後に
	// 次のフレームで必要な情報をメンバ変数に保存しておく

	UpdateMove();
	UpdateAttack();
	UpdateDash();
	UpdateChange();
	UpdateShot();
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		OnDamage();
	};
	
}

void Player::UpdateDead()
{
	if (m_isDead)
	{
		// アニメーションの更新
		m_animFrame++;
		int totalFrame = kDeadAnimNum * kSingleAnimFrame;
		if (m_animFrame >= totalFrame)
		{
			return;
		}
	}
}

void Player::UpdateMove()
{
	m_isMove = false;
	if (!m_isDash)
	{
		m_isDirLeft = false;
		m_isDirRight = false;
		m_isDirUp = false;
		m_isDirDown = false;
	}

	
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// 左キーを押しているときの処理
		m_pos.x -= kSpeed;  // 左方向に位置を変更
		m_isMove = true;
		if (!m_isAttack)
		{
			m_isDirLeft = true; // 攻撃中以外はキャラが左を向いている
		}
	
	}

	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// 右キーを押しているときの処理
		m_pos.x += kSpeed;   // 右方向に位置を変更
		m_isMove = true;
		if (!m_isAttack)
		{
			m_isDirRight = true;
		}
	
	}

	if (Pad::IsPress(PAD_INPUT_UP))
	{
		// 上キーを押しているときの処理
		m_pos.y -= kSpeed;
		m_isDirUp = true;
		m_isMove = true;
		
	}

	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		// 下キーを押しているときの処理
		m_pos.y += kSpeed;
		m_isDirDown = true;
		m_isMove = true;
	
	}
	/*m_pos.Normalize();*/

	if (m_pos.x < kGraphWidth)
	{
		m_pos.x = kGraphWidth;
	}
	if (m_pos.x > Game::kScreenWidth / 2 - kGraphWidthBig / 2)
	{
		m_pos.x = Game::kScreenWidth / 2- kGraphWidthBig / 2;
	}
	if (m_pos.y < kGraphHeight)
	{
		m_pos.y = kGraphHeight;
	}
	if (m_pos.y > Game::kScreenHeight)
	{
		m_pos.y = Game::kScreenHeight;
	}

}

void Player::UpdateAttack()
{
	// 攻撃

	if (!m_isAttack && !m_isChange && !m_isDash)
	{
		if (Pad::IsPress(PAD_INPUT_3) || Pad::IsPress(PAD_INPUT_2))
		{
			m_isAttack = true;
			m_isShot = true;
			m_animFrame = 0;
			m_isDirRight = true;
			InitShot();
			for (int i = 0; i < SHOT; i++)
			{
				// 弾iが画面上にでていない場合はその弾を画面に出す
				if (!m_ShotBotton)
				{

					shot_pos.x = (kGraphWidth - kShotGraphWidth) / 2 + m_pos.x;
					shot_pos.y = (kGraphHeight / 2 - kShotGraphHeight) / 2 + m_pos.y;

					// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する				
					m_ShotBotton = true;

					// 一つ弾を出したので弾を出すループから抜けます
					break;
				}
			}
		}
	}
}

void Player::UpdateDash()
{
	if (!m_isAttack)
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			if (!m_isDash)
			{
				m_isDash = true;
				m_DashSpeed = kDashPower;
			}
		}

		if (m_isDash)
		{

			if (m_isDirLeft)
			{

				m_pos.x -= m_DashSpeed;  // 左方向に位置を変更
				m_DashSpeed += kDeceleration;

			}

			if (m_isDirRight)
			{

				m_pos.x += m_DashSpeed;  // 右方向に位置を変更
				m_DashSpeed -= kDeceleration;

			}

			if (m_isDirUp)
			{

				m_pos.y -= m_DashSpeed;  // 上方向に位置を変更
				m_DashSpeed += kDeceleration;

			}

			if (m_isDirDown)
			{

				m_pos.y += m_DashSpeed;  // 下方向に位置を変更
				m_DashSpeed -= kDeceleration;

			}

			if (m_DashSpeed > 0.0f)
			{
				// ダッシュを終了する
				m_isDash = false;
				m_DashSpeed = 0.0f;
			}
		}

		if (Pad::IsTrigger(PAD_INPUT_1) && !m_isDash)
		{
			m_isLastDashButton = true;
			m_animFrame = 0;
		}
		else
		{
			m_isLastDashButton = false;
		}
	}

}

void Player::UpdateChange()
{
	if (!m_isChange && !m_isAttack)
	{
		if (Pad::IsTrigger(PAD_INPUT_4))
		{
			m_isChargingFrame = 0.0f;
			m_isChange = true;
			m_animFrame = 0;

			if (!m_isShot)
			{
				m_Chant++;
				if (m_Chant==1)
				{
					m_Change = 0;
				}
				if (m_Chant==2)
				{
					m_Change = 1;
				}
				if (m_Chant == 3)
				{
					m_Change = 2;
					m_Chant = 0;
				}
			}
		}
	}

}

void Player::UpdateShot()
{
	if (m_Change == 0)
	{
		shot_pos.x += IceShotSpeed;
	}
	if (m_Change == 1)
	{
		shot_pos.x += ThunderShotSpeed;
	}
	if (m_Change == 2)
	{
		shot_pos.x += AirShotSpeed;
	}

	int ShotFrame = 0;

	if (m_Change == 0)
	{
		ShotFrame = kShotIce_AnimNum * kSingleAnimFrame;
		if (m_animFrame >= ShotFrame)
		{
			m_animFrame = 0;
		}
	}

	if (m_Change == 1)
	{
		ShotFrame = kShotThunder_AnimNum * kSingleAnimFrame;
		if (m_animFrame >= ShotFrame)
		{
			m_animFrame = 0;
		}
	}

	if (m_Change == 2)
	{
		ShotFrame = kShotAir_AnimNum * kSingleAnimFrame;
		if (m_animFrame >= ShotFrame)
		{
			m_animFrame = 0;
		}
	}

	if (m_isShot)
	{
		if (m_Change == 0)
		{
			if (shot_pos.x > Game::kScreenWidth)
			{
				m_isShot = false;
				m_ShotBotton = false;
				EndShot();
			}
		}
		if (m_Change == 1)
		{
			if (shot_pos.x > Game::kScreenWidth)
			{
				m_isShot = false;
				m_ShotBotton = false;
				EndShot();
			}
		}
		if (m_Change == 2)
		{
			if (shot_pos.x > Game::kScreenWidth)
			{
				m_isShot = false;
				m_ShotBotton = false;
				EndShot();
			}
		}






	}

}

void Player::Draw()
{
	// 使用するグラフィックのハンドルを一旦別のint型変数に格納する
	int useHandle = m_handleIdle;
	if (m_isMove)
	{
		useHandle = m_handleMove;
	}
	if (m_isAttack || m_isChange)
	{
		useHandle = m_handleAttack;
	}
	if (m_isDead)
	{
		useHandle = m_handleDead;
	}


	int animNo = m_animFrame / kSingleAnimFrame;
	
	if (m_isChange)
	{
		if (animNo >= 3)
		{
			animNo = 3;
		}
	}

	if (m_isDead)
	{
		if (animNo >= 6)
		{
			animNo = 6;
		}
	}

	if (m_isDirLeft == true)
	{
		m_ishir = true;
	}
	if (m_isDirRight == true)
	{
		m_ishir = false;

	}

	DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight, 1.5, 0,
		useHandle, true, m_ishir, false);

	DrawCircle(Player_HitCircleX(),Player_HitCircleY(),Player_HitCircleRad(), 0xffffff, false);

	if (m_isShot)
	{
		DrawShot();
	}
}

void Player::DrawShot()
{
	int shotanimNo = m_animFrame / kSingleAnimFrame;
	int m_NextShot = -1;

	if (m_Change == 0)
	{
		m_NextShot = m_handleIce_Shot;
	}

	if (m_Change == 1)
	{
		m_NextShot = m_handleThunder_Shot;
	}

	if (m_Change == 2)
	{
		m_NextShot = m_handleAir_Shot;
	}

	DrawRectRotaGraph(static_cast<int>(shot_pos.x - kShotGraphWidth / 2), static_cast<int>(shot_pos.y - kShotGraphHeight),
		shotanimNo * kShotGraphWidth, 0, kShotGraphWidth, kShotGraphHeight,1.2,0,
		m_NextShot, true, false, false);

	DrawCircle(Shot_CircleX(), Shot_CircleY(), Shot_CircleRad(), 0xffffff, false);
}

void Player::End()
{
	DeleteGraph(m_handleIdle);
	DeleteGraph(m_handleMove);
	DeleteGraph(m_handleAttack);
	DeleteGraph(m_handleDead);
}
void Player::EndShot()
{
	DeleteGraph(m_handleIce_Shot);
	DeleteGraph(m_handleThunder_Shot);
	DeleteGraph(m_handleAir_Shot);
}