#pragma once
#include "../SceneManager/SceneManager.h"
class SceneGameClear
{
public:
	SceneGameClear();
	~SceneGameClear();

	void Init();
	SceneManager::SceneKind Update();
	void Draw();
	void End();
private:
	int m_blinkFrameCount;
	// �_�Ŏ���
	const int kBlinkCycleFrame = 60;
	// �t�H���g�ύX
	int m_fontHandle;
	int m_fontHandle2;
};


