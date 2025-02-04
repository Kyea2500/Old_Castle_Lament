#pragma once
//#include "../SceneGameOver/SceneGameOver.h"
//#include"../SceneClear/SceneClear.h"
#include <memory>

class SceneTitle;
class SceneGame;
class SceneGameOver;
class SceneGameClear;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();
public:
	enum SceneKind
	{
		kSceneTitle,
		kSceneGame,
		kSceneGameOver,
		kSceneGameClear,
		kSceneNum
	};

	
private:
	SceneKind m_Kind;
	// �e�V�[���̃|�C���^
	SceneTitle* m_pSceneTitle;
	SceneGame* m_pSceneGame;
	SceneGameOver* m_pSceneGameOver;
	SceneGameClear* m_pSceneGameClear;
};