#include "DxLib.h"
#include"Scene/SceneManager/SceneManager.h"
#include"Scene/SceneClear/SceneClear.h"
#include"GameProcess/Game.h"
#include"resource.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �t���X�N���[���ł͂Ȃ��A�E�B���h�E���[�h�ŊJ���悤�ɂ���
	ChangeWindowMode(Game::kDefaultWindowMode);

	SetWindowText(L"�Ï�̃�����");
	SetWindowIconID(IDI_ICON3);
	
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// �^�C�g���̕ύX
	
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	/*SceneGameClear* pScene = new SceneGameClear();*/
	SceneManager* pScene = new SceneManager();
	pScene->Init();

	//Player* m_player = new Player();	//�R���X�g���N�^�ɓ���
	//m_player->Init();				//�����������ɓ���
	//Boss* m_boss = new Boss();
	//m_boss->Init();


	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		// ���[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();
		// ��ʂ��N���A��
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		pScene->Update();
		pScene->Draw();
		
		//m_player->Update();//�X�V�����ɓ���
		//m_player->Draw();	//�`�揈���ɓ���

		//m_boss->Update();
		//m_boss->Draw();


		// ��ʂ̐؂�ւ���҂K�v������
		ScreenFlip();
		//FPS(Frame Per Second)60�ɌŒ�

		// esc�L�[�ŏI��(��������I��)
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}

	}

	//m_player->End();//��������ɓ���

	//m_player = nullptr; //�|�C���^�𖳌��l
	//delete(m_player);	//�f�X�g���N�^���Ă΂��

	//m_boss = nullptr;
	//delete(m_boss);
	pScene->End();

	pScene = nullptr;
	delete(pScene);

	DxLib_End();		// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}