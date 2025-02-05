#include "SceneTitle.h"
#include <DxLib.h>
#include "../../GameProcess/Pad/Pad.h"
#include "../SceneManager/SceneManager.h"
#include"../../GameProcess/Game.h"

namespace
{
	// �����̓_��
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// �����̕\���ʒu
	constexpr int kTitleY = 200;
	constexpr int kButtonTextY = Game::kScreenHeight - 100;
	const int Color = GetColor(180, 70, 70);
	const int Colors = GetColor(35, 35, 35);
}

SceneTitle::SceneTitle() :
	m_titleGraph(-1),
	m_fontHandle(-1),
 m_blinkFrameCount(0)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// �t�H���g�̐���
	m_fontHandle = CreateFontToHandle(L"BIZ UD���� Medium", 32, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	// �^�C�g���摜�̓ǂݍ���
	m_titleGraph = LoadGraph(L"../date/image/Title.png");
	
}

SceneManager::SceneKind SceneTitle::Update()
{
	// 1�b�T�C�N���ŕ\���A��\����؂�ւ���
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}
	
	/* 1�{�^������������Main�Ɉڍs����*/
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind::kSceneGame;

	}

	// �������Ȃ���΃V�[���͑J�ڂ��Ȃ�(�^�C�g����ʂ̂܂�)
	return SceneManager::SceneKind::kSceneTitle;
}

void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Colors, true);
	// �^�C�g���摜��`��
	/*DrawGraph(kScreenWidth, 0, m_titleGraph, TRUE);*/
	DrawRotaGraph(Game::kScreenWidth/2, Game::kScreenHeight/2,
		 0.6,0,
		m_titleGraph,true,false);
	// 1�b�T�C�N���ŕ\���A��\����؂�ւ���
	// 1�{�^���������Ă�������
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		int width = GetDrawStringWidthToHandle(L"�{�^���������Ă�������", strlen("1�{�^���������Ă�������"),m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, kButtonTextY, L"1�{�^���������Ă�������", Color, m_fontHandle);
	}
}

void SceneTitle::End()
{
	DeleteGraph(m_titleGraph);
	DeleteFontToHandle(m_fontHandle);
}
