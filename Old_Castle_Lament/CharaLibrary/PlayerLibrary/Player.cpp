#include "Player.h"
#include "../../GameProcess/Pad/Pad.h"
#include"../�v���W�F�N�g�ɒǉ����ׂ��t�@�C��_VC�p/DxLib.h"
#include"../../GameProcess/Game.h"


namespace
{
	// �L�����N�^�[�O���t�B�b�N�̕��ƍ���
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;
	constexpr int kGraphSize = 32;

	// �g��k����
	constexpr float ChangeSize = 1.5f;
	constexpr float ChangeShotSize = 1.2f;
	constexpr int half = 2;
	constexpr int kGraphWidthBig = 32 * 1.5;
	constexpr int kGraphHeightBig = 32 * 1.5;

	// �L�����N�^�[�̓����蔻��
	constexpr float P_CircleX =  kGraphWidth / 2;
	constexpr float P_CircleY =  kGraphHeight;
	constexpr float P_CircleR = kGraphSize / 2 / 1.5;

	// �e�̃O���t�B�b�N�̕��ƍ���
	constexpr int kShotGraphWidth = 48;
	constexpr int kShotGraphHeight = 32;
	constexpr int kShotSize = 32*1.2;

	constexpr float S_CircleX = kShotGraphWidth / 2;
	constexpr float S_CircleY = kShotGraphHeight;
	constexpr float S_CircleR = kShotSize / 3;

	// �A�j���[�V�����̃R�}��
	constexpr int kIdleAnimNum = 2;
	constexpr int kRunAnimNum = 8;
	constexpr int kAttackAnimNum = 8;
	constexpr int kDeadAnimNum = 8;

	constexpr int kShotIce_AnimNum = 10;
	constexpr int kShotThunder_AnimNum = 16;
	constexpr int kShotAir_AnimNum = 14;

	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 5;

	// �L�����N�^�[�̈ړ����x
	constexpr float kSpeed = 3.0f;

	// �v���C���[�̖��@(�e)�̑��x
	constexpr float IceShotSpeed = 6.0f;
	constexpr float ThunderShotSpeed = 9.0f;
	constexpr float AirShotSpeed = 12.0f;

	// �L�����N�^�[��X��
	constexpr float kPosX = 320.0f;
	constexpr float kPosY = Game::kScreenHeight - 128.0f;

	// �_�b�V���̏���
	constexpr float kDashPower = 10.0f; // �_�b�V���̉����l
	constexpr float kDeceleration = 0.4f; // �_�b�V���̌����l

	// �_���[�W�H�������̖��G����
	constexpr int kDamageBlinkFrame = 60;

	// ������є���
	constexpr float kBlown_Away = 32.1f;
	constexpr float kDeadBlown = 2.0f;

	// �s���ԍ�
	constexpr int first = 1;
	constexpr int second = 2;
	constexpr int third = 3;

	// ��苗���ȉ��Ȃ�ˌ����֎~����
	constexpr float ShotBanArea = 3.18f;

	// �e���ꂩ�����
	constexpr int Endlessly_Ahead = 2000;

	// �A�j���[�V�������~�߂�(�w��ȏ��ɂ���`��̍폜)
	constexpr int StopAnimNo_isChange = 3;
	constexpr int StopAnimNo_isDead = 6;
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
	m_blinkFrameCount(0)	
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
	m_blinkFrameCount--;
	if (m_blinkFrameCount < 0)
	{
		m_blinkFrameCount = 0;
	}
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
	if (m_blinkFrameCount > 0) return;
	// ���G����(�_�ł��鎞��)��ݒ肷��
	m_blinkFrameCount = kDamageBlinkFrame;
	m_Life--;
	m_pos.x -= kBlown_Away;	
	// HP��0�ȉ��ɂȂ����玀�S���o���J�n����
	if (m_Life <= 0)
	{
		m_isDead = true;
	}
	return;
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
	// �A�j���[�V�����̍X�V
	m_animFrame++;
	// �A�j���[�V�����̑S�̐�
	int totalFrame = kIdleAnimNum * kSingleAnimFrame;
	if (m_isMove)
	{
		totalFrame = kRunAnimNum * kSingleAnimFrame;
	}
	// �A�j���[�V�����̍��v�t���[�����𒴂�����ŏ��ɖ߂�
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


	// �ړ����Ă��Ȃ��Ƃ��A�t���O�����낷
#ifdef DISP_COLLISION
	if(m_Change==0)DrawFormatString(0,Game::kScreenHeight- kGraphHeight, 0xffffff, L"IceShot");
	if(m_Change==1)DrawFormatString(0,Game::kScreenHeight - kGraphHeight, 0xffffff, L"ThunderShot");
	if(m_Change==2)DrawFormatString(0,Game::kScreenHeight - kGraphHeight, 0xffffff, L"AirShot");
#endif
	if (m_isMove != isLastRun)
	{
		m_animFrame = 0;
	}

	// ��A�̏������s�������
	// ���̃t���[���ŕK�v�ȏ��������o�ϐ��ɕۑ����Ă���

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
		// �A�j���[�V�����̍X�V
		m_pos.x -= kDeadBlown;
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
		// ���L�[�������Ă���Ƃ��̏���
		m_pos.x -= kSpeed;  // �������Ɉʒu��ύX
		m_isMove = true;
		if (!m_isAttack)
		{
			m_isDirLeft = true; // �U�����ȊO�̓L���������������Ă���
		}
	
	}

	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// �E�L�[�������Ă���Ƃ��̏���
		m_pos.x += kSpeed;   // �E�����Ɉʒu��ύX
		m_isMove = true;
		if (!m_isAttack)
		{
			m_isDirRight = true;
		}
	
	}

	if (Pad::IsPress(PAD_INPUT_UP))
	{
		// ��L�[�������Ă���Ƃ��̏���
		m_pos.y -= kSpeed;
		m_isDirUp = true;
		m_isMove = true;
		
	}

	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		// ���L�[�������Ă���Ƃ��̏���
		m_pos.y += kSpeed;
		m_isDirDown = true;
		m_isMove = true;
	
	}
	/*m_pos.Normalize();*/

	if (m_pos.x < kGraphWidth)
	{
		m_pos.x = kGraphWidth;
	}
	if (m_pos.x > Game::kScreenWidth / half - kGraphWidthBig / half)
	{
		m_pos.x = Game::kScreenWidth / half - kGraphWidthBig / half;
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
	// �U��

	if (!m_isAttack && !m_isChange && !m_isDash)
	{
		if (Pad::IsPress(PAD_INPUT_3) || Pad::IsPress(PAD_INPUT_2))
		{
			m_isAttack = true;
			m_animFrame = 0;
			m_isDirRight = true;
			if (m_pos.x >= Game::kScreenWidth/ ShotBanArea)
			{
				m_isShot = true;
				InitShot();
				for (int i = 0; i < SHOT; i++)
				{
					// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
					if (!m_ShotBotton)
					{
						shot_pos.x = (kGraphWidth - kShotGraphWidth) / half + m_pos.x;
						shot_pos.y = (kGraphHeight / half - kShotGraphHeight) / half + m_pos.y;

						// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������				
						m_ShotBotton = true;

						// ��e���o�����̂Œe���o�����[�v���甲���܂�
						break;
					}
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

				m_pos.x -= m_DashSpeed;  // �������Ɉʒu��ύX
				m_DashSpeed += kDeceleration;

			}

			if (m_isDirRight)
			{

				m_pos.x += m_DashSpeed;  // �E�����Ɉʒu��ύX
				m_DashSpeed -= kDeceleration;

			}

			if (m_isDirUp)
			{

				m_pos.y -= m_DashSpeed;  // ������Ɉʒu��ύX
				m_DashSpeed += kDeceleration;

			}

			if (m_isDirDown)
			{

				m_pos.y += m_DashSpeed;  // �������Ɉʒu��ύX
				m_DashSpeed -= kDeceleration;

			}

			if (m_DashSpeed > 0.0f)
			{
				// �_�b�V�����I������
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
				if (m_Chant==first)
				{
					m_Change = 0;
				}
				if (m_Chant== second)
				{
					m_Change = first;
				}
				if (m_Chant == third)
				{
					m_Change = second;
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
	if (m_Change == first)
	{
		shot_pos.x += ThunderShotSpeed;
	}
	if (m_Change == second)
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

	if (m_Change == first)
	{
		ShotFrame = kShotThunder_AnimNum * kSingleAnimFrame;
		if (m_animFrame >= ShotFrame)
		{
			m_animFrame = 0;
		}
	}

	if (m_Change == second)
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
				HitShot();
			}
		}
		if (m_Change == first)
		{
			if (shot_pos.x > Game::kScreenWidth)
			{
				HitShot();
			}
		}
		if (m_Change == second)
		{
			if (shot_pos.x > Game::kScreenWidth)
			{
				HitShot();
			}
		}
	}
	

}

void Player::HitShot()
{
	shot_pos.y = Endlessly_Ahead;
	m_isShot = false;
	m_ShotBotton = false;
	EndShot();

}

void Player::Draw()
{
	if ((m_blinkFrameCount / half) % half)
	{
		return;
	}
	// �g�p����O���t�B�b�N�̃n���h������U�ʂ�int�^�ϐ��Ɋi�[����
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
		if (animNo >= StopAnimNo_isChange)
		{
			animNo = StopAnimNo_isChange;
		}
	}

	if (m_isDead)
	{
		if (animNo >= StopAnimNo_isDead)
		{
			animNo = StopAnimNo_isDead;
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

	DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth / half), static_cast<int>(m_pos.y - kGraphHeight),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight, ChangeSize, 0,
		useHandle, true, m_ishir, false);
#ifdef DISP_COLLISION
	DrawCircle(Player_HitCircleX(),Player_HitCircleY(),Player_HitCircleRad(), 0xffffff, false);
#endif

	if (m_isShot)
	{
		DrawShot();
	}
}

void Player::DrawShot()
{
	int shotanimNo = m_animFrame / kSingleAnimFrame;
	int m_NextShot = 0;

	if (m_Change == 0)
	{
		m_NextShot = m_handleIce_Shot;
	}

	else if (m_Change == first)
	{
		m_NextShot = m_handleThunder_Shot;
	}

	else if (m_Change == second)
	{
		m_NextShot = m_handleAir_Shot;
	}

	DrawRectRotaGraph(static_cast<int>(shot_pos.x - kShotGraphWidth / half), static_cast<int>(shot_pos.y - kShotGraphHeight),
		shotanimNo * kShotGraphWidth, 0, kShotGraphWidth, kShotGraphHeight, ChangeShotSize,0,
		m_NextShot, true, false, false);
#ifdef DISP_COLLISION
	DrawCircle(Shot_CircleX(), Shot_CircleY(), Shot_CircleRad(), 0xffffff, false);
#endif
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