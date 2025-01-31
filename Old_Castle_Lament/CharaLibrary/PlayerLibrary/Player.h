#pragma once
#include "../../Vec2/Vec2.h"
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();		//�R���X�g���N�^
	~Player();		//�f�X�g���N�^

	void Init();	//������
	void Update();	//�X�V
	void Draw();	//�`��
	void End();		//���
public:
	void OnDamage();

	void UpdateNormal(); // �Q�[������Update
	void UpdateDead();   // ���S���Update
	void InitShot();
	void UpdateShot();
	void DrawShot();
	void EndShot();

	// �v���C���[�̓����蔻��
	float Player_HitCircleX();
	float Player_HitCircleY();
	float Player_HitCircleRad();
	
	// �e�̓����蔻��
	float Shot_CircleX();
	float Shot_CircleY();
	float Shot_CircleRad();

private:
	void UpdateMove();
	void UpdateAttack();
	void UpdateDash();
	void UpdateChange();
	

	// �� �e��ɕK�v�Ȋ֐�
	// �ҋ@
	int m_handleIdle;
	// �ړ�
	int m_handleMove;
	// �U��
	int m_handleAttack;
	// �e�̎��
	int m_handleIce_Shot;		// �X�e�@�Η͂������A���x�͒x��
	int m_handleThunder_Shot;	// ���e�@�Η͂����ԁA���x������
	int m_handleAir_Shot;		// ���e�@�Η͂��Ⴍ�A���x�͑���
	//�ϋv�l�Q�[�W
	int m_handleLife;
	// ���S
	int m_handleDead;
	bool m_isDead;
	// �v���C���[�̕\���ʒu
	Vec2 m_pos;
	// �e�̕\���ʒu
	Vec2 shot_pos;

	// �̗͏���
	int m_Life;
	bool m_isDamage;

	//�@�ړ������@
	bool m_isDirLeft;	// true:������ 
	bool m_isDirRight;	// true:�E���� 
	bool m_isDirUp;		// true:���	
	bool m_isDirDown;	// true:����

	// �L�����N�^�[�������Ă������
	bool m_ishir;	// true:�������@false:�E����

	// �A�j���[�V�����֘A
	int m_animFrame; // �t���[�����𐔂���

	// �ړ�����
	bool m_isMove;		// true:�����Ă���	false:�ҋ@
	// �ړ��l���������
	float m_isSpeed;

	// �_�b�V������
	bool m_isDash;		// true:�f�����ړ��@false:�ω��Ȃ�
	// �_�b�V���l���������
	float m_DashSpeed;
	// �_�b�V���{�^���̃g���K�[����
	// 1�O�̃t���[���Ƀ_�b�V���{�^����������Ă������ǂ������o���Ă���
	bool m_isLastDashButton;

	// �U���̏���
	bool m_isAttack;	// true:�U���@false:�ω��Ȃ�
	// true:�e�������Ă���@false:�e�������Ă��Ȃ�
	bool m_isShot;
	// true:�ˌ��{�^�����������@false:�ˌ��{�^���������Ă��Ȃ�
	bool m_ShotBotton;

	// ���@�̐؂�ւ�����
	bool m_isChange;	//true:�؂�ւ��@false:�ω��Ȃ�
	// �ēx�؂�ւ��邽�߂̃N�[���^�C��(�A���؂�ւ��֎~����)
	float m_isChargingFrame;
	int m_Chant;
	// �e�̐؂�ւ��@0:�X�e�@1:���e�@2:���e
	int m_Change;

	int m_blinktime;
};

