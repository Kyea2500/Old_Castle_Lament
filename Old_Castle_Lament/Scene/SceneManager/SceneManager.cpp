#include "SceneManager.h"
#include "../SceneTitle/SceneTitle.h"
#include "../SceneGame/SceneGame.h"
#include"../SceneGameOver/SceneGameOver.h"
#include"../SceneClear/SceneClear.h"
#include"../../GameProcess/Pad/Pad.h"

SceneManager::SceneManager():m_Kind(kSceneTitle),
m_pSceneTitle(nullptr),
m_pSceneGame(nullptr),
m_pSceneGameOver(nullptr),
m_pSceneGameClear(nullptr)
{
}

SceneManager::~SceneManager()
{
	if (m_pSceneTitle != nullptr)
	{
		m_pSceneTitle = nullptr;
		delete m_pSceneTitle;
	}

	else if (m_pSceneGame != nullptr)
	{
		m_pSceneGame = nullptr;
		delete m_pSceneGame;
	}

	else if (m_pSceneGameOver != nullptr)
	{
		m_pSceneGameOver = nullptr;
		delete m_pSceneGameOver;
	}
	else if (m_pSceneGameClear != nullptr)
	{
		m_pSceneGameClear = nullptr;
		delete m_pSceneGameClear;
	}
}

void SceneManager::Init()
{
	switch (m_Kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle = new SceneTitle;
	m_pSceneTitle->Init();
	break;
	case SceneManager::kSceneGame:
		m_pSceneGame = new SceneGame;
	m_pSceneGame->Init();
		break;
	case SceneManager::kSceneGameOver:
		m_pSceneGameOver = new SceneGameOver;
	m_pSceneGameOver->Init();
		break;
	case SceneManager::kSceneGameClear:
		m_pSceneGameClear = new SceneGameClear;
		m_pSceneGameClear->Init();
		break;
	case SceneManager::kSceneNum:
	default:
		break;
	}
}
void SceneManager::End()
{
	switch (m_Kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->End();
		delete m_pSceneTitle;
		m_pSceneTitle = nullptr;
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->End();
		delete m_pSceneGame;
		m_pSceneGame = nullptr;
		break;
	case SceneManager::kSceneGameOver:
		m_pSceneGameOver->End();
		delete m_pSceneGameOver;
		m_pSceneGameOver = nullptr;
		break;
	case SceneManager::kSceneGameClear:
		m_pSceneGameClear->End();
		delete m_pSceneGameClear;
		m_pSceneGameClear = nullptr;
		break;
	case SceneManager::kSceneNum:
	default:
		break;
	}
}
void SceneManager::Update()
{
	Pad::Update();
	SceneKind nextKind = m_Kind;
	switch (m_Kind)
	{
	case SceneManager::kSceneTitle:
		nextKind = m_pSceneTitle->Update();
		break;
	case SceneManager::kSceneGame:
		nextKind = m_pSceneGame->Update();
		break;
	case SceneManager::kSceneGameOver:
		nextKind = m_pSceneGameOver->Update();
		break;
	case SceneManager::kSceneGameClear:
		nextKind = m_pSceneGameClear->Update();
		break;
	case SceneManager::kSceneNum:
	default:
		break;
	}
	if (nextKind != m_Kind)
	{
		// 現在実行中のシーン(m_kind)の終了処理
		End();
		// 次のシーンに切り替え
		m_Kind = nextKind;
		// 切り替え後のシーンの初期化
		Init();
	}
}

void SceneManager::Draw()
{
	switch (m_Kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Draw();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->Draw();
		break;
	case SceneManager::kSceneGameOver:
		m_pSceneGameOver->Draw();
		break;
	case SceneManager::kSceneGameClear:
		m_pSceneGameClear->Draw();
		break;
	case SceneManager::kSceneNum:
	default:
		break;
	}
}



