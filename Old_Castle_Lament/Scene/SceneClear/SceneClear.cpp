#include "SceneClear.h"
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
	const int Color = GetColor(160, 180, 180);
	const int Color2 = GetColor(200, 180, 180);
	const int Colors = GetColor(50, 30, 50);

	constexpr int TextSize = 128;
	constexpr int TextsSize = 32;
	constexpr int half = 2;
}

SceneGameClear::SceneGameClear():m_fontHandle(-1),
m_blinkFrameCount(0), m_fontHandle2(-1)
{

}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
	m_fontHandle = CreateFontToHandle(L"BIZ UD明朝 Medium", TextSize, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	m_fontHandle2 = CreateFontToHandle(L"HGP教科書体", TextsSize, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

SceneManager::SceneKind SceneGameClear::Update()
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
	return SceneManager::SceneKind::kSceneGameClear;
}

void SceneGameClear::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Colors, true);
	int width = GetDrawStringWidthToHandle(L"GAME CLEAR!", strlen("GAME CLEAR!"), m_fontHandle);
	DrawStringToHandle(Game::kScreenWidth / half / half, Game::kScreenHeight / half - TextSize,
		L"GAME CLEAR!", Color, m_fontHandle);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		int Widths = GetDrawStringWidthToHandle(L"ボタンでタイトルに戻る", strlen("1ボタンでタイトルに戻る"), m_fontHandle2);
		DrawStringToHandle(Game::kScreenWidth / 2 - Widths / 2, kButtonTextY, L"1ボタンでタイトルに戻る", Color2, m_fontHandle2);
	}
}

void SceneGameClear::End()
{
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle2);
}
