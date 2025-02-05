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
	// フォントの生成
	m_fontHandle = CreateFontToHandle(L"BIZ UD明朝 Medium", 32, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
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
	DrawRotaGraph(Game::kScreenWidth/2, Game::kScreenHeight/2,
		 0.6,0,
		m_titleGraph,true,false);
	// 1秒サイクルで表示、非表示を切り替える
	// 1ボタンを押してください
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		int width = GetDrawStringWidthToHandle(L"ボタンを押してください", strlen("1ボタンを押してください"),m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, kButtonTextY, L"1ボタンを押してください", Color, m_fontHandle);
	}
}

void SceneTitle::End()
{
	DeleteGraph(m_titleGraph);
	DeleteFontToHandle(m_fontHandle);
}
