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

	// �F�̍쐬
	const int Color = GetColor(180, 70, 70);
	const int Colors = GetColor(35, 35, 35);
	
	// �e��v�Z����ѐ��l
	constexpr int Half = 2;
	constexpr int InitialGraph = -1;
	constexpr int FontSize = 32;
	constexpr float magnification = 0.6f;
}

SceneTitle::SceneTitle() :
	m_titleGraph(InitialGraph),
	m_fontHandle(InitialGraph),
 m_blinkFrameCount(0)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// �t�H���g�̐���
	m_fontHandle = CreateFontToHandle(L"BIZ UD���� Medium", FontSize, InitialGraph, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
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
	DrawRotaGraph(Game::kScreenWidth/Half, Game::kScreenHeight/ Half,
		magnification,0,
		m_titleGraph,true,false);
	// 1�b�T�C�N���ŕ\���A��\����؂�ւ���
	// 1�{�^���������Ă�������
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		int width = GetDrawStringWidthToHandle(L"�{�^���������Ă�������", strlen("A�{�^���������Ă�������"),m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / Half - width / Half, kButtonTextY, L"A�{�^���������Ă�������", Color, m_fontHandle);
	}
}

void SceneTitle::End()
{
	DeleteGraph(m_titleGraph);
	DeleteFontToHandle(m_fontHandle);
}
