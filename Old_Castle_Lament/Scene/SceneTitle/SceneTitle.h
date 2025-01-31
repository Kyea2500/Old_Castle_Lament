#pragma once
#include "../../Scene/SceneManager/SceneManager.h"

class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	//SceneManager::Kind Update(); 
	void Draw();
	void End();
private:
	int m_titleGraph;
	// �_�ŏ���
	int m_blinkFrameCount;
	// �_�Ŏ���
	const int kBlinkCycleFrame = 60;
	// �t�H���g�ύX
	int m_fontHandle;
};
