#pragma once
#include "../SceneManager/SceneManager.h"
class SceneGameOver
{
public:
	SceneGameOver();
	~SceneGameOver();

	void Init();
	SceneManager::SceneKind Update();
	void Draw();
	void End();
private:
	int m_blinkFrameCount;
	// �_�Ŏ���
	const int kBlinkCycleFrame = 80;
	// �t�H���g�ύX
	int m_fontHandle;
	int m_fontHandle2;
};

