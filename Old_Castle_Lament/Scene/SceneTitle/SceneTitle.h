#pragma once
#include "../SceneManager/SceneManager.h"
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	//void Update();
	SceneManager::SceneKind Update();
	void Draw();
	void End();
private:
	int m_titleGraph;
	// 点滅処理
	int m_blinkFrameCount;
	// 点滅周期
	const int kBlinkCycleFrame = 60;
	// フォント変更
	int m_fontHandle;
};
