#include "SceneTitle.h"
#include <DxLib.h>
#include "../../GameProcess/Pad/Pad.h"
#include "../SceneManager/SceneManager.h"
#include"../../GameProcess/Game.h"

namespace
{
	// 文字の点滅
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// 文字の表示位置
	constexpr int kTitleY = 200;
	constexpr int kButtonTextY = Game::kScreenHeight - 100;

	// 色の作成
	const int Color = GetColor(180, 70, 70);
	const int Colors = GetColor(35, 35, 35);
	
	// 各種計算および数値
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
	// フォントの生成
	m_fontHandle = CreateFontToHandle(L"BIZ UD明朝 Medium", FontSize, InitialGraph, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	// タイトル画像の読み込み
	m_titleGraph = LoadGraph(L"../date/image/Title.png");
	
}

SceneManager::SceneKind SceneTitle::Update()
{
	// 1秒サイクルで表示、非表示を切り替える
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}
	
	/* 1ボタンを押したらMainに移行する*/
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind::kSceneGame;

	}

	// 何もしなければシーンは遷移しない(タイトル画面のまま)
	return SceneManager::SceneKind::kSceneTitle;
}

void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Colors, true);
	// タイトル画像を描画
	/*DrawGraph(kScreenWidth, 0, m_titleGraph, TRUE);*/
	DrawRotaGraph(Game::kScreenWidth/Half, Game::kScreenHeight/ Half,
		magnification,0,
		m_titleGraph,true,false);
	// 1秒サイクルで表示、非表示を切り替える
	// 1ボタンを押してください
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		int width = GetDrawStringWidthToHandle(L"ボタンを押してください", strlen("Aボタンを押してください"),m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / Half - width / Half, kButtonTextY, L"Aボタンを押してください", Color, m_fontHandle);
	}
}

void SceneTitle::End()
{
	DeleteGraph(m_titleGraph);
	DeleteFontToHandle(m_fontHandle);
}
