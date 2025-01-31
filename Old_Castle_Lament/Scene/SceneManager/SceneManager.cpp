#include "SceneManager.h"

SceneManager::SceneManager()
	: Kind(kSceneTitle)
{
	//m_pSceneTitle=std::make_shared<SceneTitle>();
	//m_pSceneGame = std::make_shared<SceneGame>();
	/*m_pSceneGameOver = std::make_shared<SceneGameOver>();
	m_pSceneGameClear = std::make_shared<SceneGameClear>();*/

	m_pSceneTitle = new SceneTitle;
	m_pSceneGame = new SceneGame;
	/*m_pSceneGameOver = new SceneGameOver;
	m_pSceneGameClear = new SceneGameClear;*/
	Kind = kSceneTitle;
}

SceneManager::~SceneManager()
{
	if (m_pSceneTitle != nullptr)
	{
		m_pSceneTitle = nullptr;
		delete m_pSceneTitle;
	}

	if (m_pSceneGame != nullptr)
	{
		m_pSceneGame = nullptr;
		delete m_pSceneGame;
	}

	/*
	if (m_pSceneGameOver != nullptr)
	{
		m_pSceneGameOver = nullptr;
		delete m_pSceneGameOver;
	}

	if (m_pSceneGameClear != nullptr)
	{
		m_pSceneGameClear = nullptr;
		delete m_pSceneGameClear;
	}*/
}

void SceneManager::Init()
{
	switch (Kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Init();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->Init();
		break;
	/*case SceneManager::kSceneGameOver:
		m_pSceneGameOver->Init();
		break;
	case SceneManager::kSceneGameClear:
		m_pSceneGameClear->Init();
		break;*/
	}
}

void SceneManager::Update()
{
	switch (Kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Update();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->Update();
		break;
	//case SceneManager::kSceneGameOver:
	//	m_pSceneGameOver->Update();
	//	break;
	//case SceneManager::kSceneGameClear:
	//	m_pSceneGameClear->Update();
	//	break;
	}
}

void SceneManager::Draw()
{
	switch (Kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Draw();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->Draw();
		break;
	/*case SceneManager::kSceneGameOver:
		m_pSceneGameOver->Draw();
		break;
	case SceneManager::kSceneGameClear:
		m_pSceneGameClear->Draw();
		break;*/
	}
}

void SceneManager::End()
{
	switch (Kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->End();
		break;
	case SceneManager::kSceneGame:
		m_pSceneGame->End();
		break;
	}
	/*case SceneManager::kSceneGameOver:
		m_pSceneGameOver->End();
		break;
	case SceneManager::kSceneGameClear:
		m_pSceneGameClear->End();
		break;
	}*/
}
