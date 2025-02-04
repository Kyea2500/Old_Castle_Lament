#include "SceneGameOver.h"
#include"DxLib.h"
#include"../../GameProcess/Game.h"
#include"../../GameProcess/Pad/Pad.h"
namespace
{
	// 文字の点滅
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// 文字の表示位置
	constexpr int kTitleY = 200;
	constexpr int kButtonTextY = Game::kScreenHeight - 200;
	const int Color = GetColor(180, 60, 30);
	const int Color2 = GetColor(80, 120, 30);
	const int Colors = GetColor(30, 30, 30);

	constexpr int TextSize = 128;
	constexpr int TextsSize = 32;
	constexpr int half = 2;
}

SceneGameOver::SceneGameOver() :m_fontHandle(-1),
m_blinkFrameCount(0), m_fontHandle2(-1)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	m_fontHandle = CreateFontToHandle(L"BIZ UD明朝 Medium", TextSize, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	m_fontHandle2 = CreateFontToHandle(L"HGP教科書体", TextsSize, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

SceneManager::SceneKind SceneGameOver::Update()
{
	
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	/* 1ボタンを押したらMainに移行する*/
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind::kSceneTitle;
	}
	return SceneManager::SceneKind();
}

void SceneGameOver::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Colors, true);
	int width = GetDrawStringWidthToHandle(L"GAME OVER", strlen("GAME OVER"), m_fontHandle);
	DrawStringToHandle(Game::kScreenWidth / half/ half, Game::kScreenHeight / half- TextSize,
		L"GAME OVER", Color, m_fontHandle);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		int Widths = GetDrawStringWidthToHandle(L"ボタンでタイトルに戻る", strlen("1ボタンでタイトルに戻る"), m_fontHandle2);
		DrawStringToHandle(Game::kScreenWidth / 2 - Widths / 2, kButtonTextY, L"1ボタンでタイトルに戻る", Color2, m_fontHandle2);
	}
}

void SceneGameOver::End()
{
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle2);
}
