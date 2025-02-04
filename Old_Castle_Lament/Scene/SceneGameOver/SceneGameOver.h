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
	// 点滅周期
	const int kBlinkCycleFrame = 80;
	// フォント変更
	int m_fontHandle;
	int m_fontHandle2;
};

